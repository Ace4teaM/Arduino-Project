using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using ArduinoAdmin.Lib;

namespace ArduinoAdmin.Fenetres
{
    /// <summary>
    /// Logique d'interaction pour EditWnd.xaml
    /// </summary>
    public partial class EditWnd : Window, IEventHandler
    {
        App app = (App)Application.Current;

        // mode d'édition
        public enum EditMode
        {
            Other = 0,
            Edit,
            Insert,
            Duplicate,
            ReadOnly
        };

        public EditWnd(string title, EditMode mode = EditMode.Edit)
        {
            InitializeComponent();

            // initialise l'interface 
            switch (mode)
            {
                case EditMode.Edit:
                    this.Title = "Editer: " + title;
                    this.okBtn.Content = "Enregistrer";
                    break;
                case EditMode.Insert:
                    this.Title = "Nouveau: " + title;
                    this.okBtn.Content = "Ajouter";
                    break;
                case EditMode.Duplicate:
                    this.Title = "Dupliquer: " + title;
                    this.okBtn.Content = "Dupliquer";
                    break;
                default:
                    this.Title = title;
                    this.okBtn.Content = "OK";
                    break;
            }
        }


        // Ajoute un élément de l'interface
        private int newRow = 0; // numero de la prochaine ligne d'insertion
        public void AddElement(UIElement el)
        {
            var rowDefinition = new RowDefinition();
            rowDefinition.Height = GridLength.Auto;
            viewGrid.RowDefinitions.Add(rowDefinition);

            el.SetValue(Grid.RowProperty, newRow++);
            el.SetValue(Grid.ColumnProperty, 0);
            this.viewGrid.Children.Add(el);

            //this.viewStack.Children.Add(el);
        }

        // Ajoute d'une vue
        public void AddView(UIElement view)
        {
            AddElement(view);
        }

        // Ajoute d'un champ de texte
        public TextBox AddInput(string libelle, string name, string value = null)
        {
            StackPanel panel = new StackPanel();
            panel.Orientation = Orientation.Vertical;
            Label lb = new Label();
            lb.Content = libelle;
            TextBox tb =  new TextBox();
            tb.Text = value;
            if (name != null)
            {
                tb.Name = name.ToLower();
                tb.SetBinding(TextBox.TextProperty, new Binding(name));
            }
            panel.Children.Add(lb);
            panel.Children.Add(tb);
            AddElement(panel);
            return tb;
        }

        // Ajoute d'un texte
        public Label AddLabel(string libelle)
        {
            Label lb = new Label();
            lb.Content = libelle;
            AddElement(lb);
            return lb;
        }

        // Ajoute d'un titre
        public Label AddTitle(string libelle)
        {
            Label lb = new Label();
            lb.Content = libelle;
            lb.Margin = new Thickness(0,10,0,4);
            lb.FontWeight = FontWeights.Bold;
            lb.FontSize = 16;
            lb.BorderThickness = new Thickness(0, 0, 0, 2);
            AddElement(lb);
            return lb;
        }

        // Ajoute d'une note
        public TextBox AddLegend(string libelle)
        {
            TextBox lb = new TextBox();
            lb.Text = libelle;
            lb.Margin = new Thickness(0, 0, 0, 16);
            lb.FontStyle = FontStyles.Italic;
            lb.FontSize = 12;
            lb.BorderThickness = new Thickness(0);
            lb.Foreground = Brushes.Blue;
            lb.TextWrapping = TextWrapping.Wrap;
            AddElement(lb);
            return lb;
        }

        // Ajoute un combobox avec une liste de choix
        public ComboBox AddSelection(string libelle, string name, string[] keys, string[] desc, string value = null, object dataContext = null)
        {
            StackPanel panel = new StackPanel();
            panel.Orientation = Orientation.Vertical;
            Label lb = new Label();
            lb.Content = libelle;
            ComboBox cb = new ComboBox();
            cb.SelectedValuePath = "Tag";
            for (int i = 0; i < keys.Count(); i++ )
            {
                ComboBoxItem item = new ComboBoxItem();
                item.Tag = keys[i];
                item.Content = desc[i];
                cb.Items.Add(item);
            }
            cb.SelectedValue = value;
            if (name != null)
            {
                cb.Name = name.ToLower();
                cb.DataContext = dataContext;
                cb.SetBinding(ComboBox.SelectedValueProperty, new Binding(name));
            }
            panel.Children.Add(lb);
            panel.Children.Add(cb);
            AddElement(panel);
            return cb;
        }
        private void Button_Click_Cancel(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
        private void Button_Click_OK(object sender, RoutedEventArgs e)
        {
            // vérifie la validité des controles (uniquement les controles actifs)
            Exception ex;
            if (Validate.IsValid(this, out ex, true) == false)
            {
                (Application.Current as App).ProcessException(ex);
                return;
            }

            //verifie la validite du contexte
            /*if (this.DataContext is IDataErrorInfo)
            {
                IDataErrorInfo err = this.DataContext as IDataErrorInfo;
                // vérifie les champs
                if (err.Error != String.Empty)
                {
                    app.ProcessException(new FormatException(err.Error));
                    return;
                }
            }*/
            // termine le dialogue
            try
            {
                this.DialogResult = true;
            }
            catch (Exception){} // si la fenetre n'est pas modal

            this.Close();
        }

        //-----------------------------------------------------------------------------------------
        // Evénements
        // Réceptionne les événements "utilisateur" provenant des autres fenêtres puis agit en conséquence.
        //-----------------------------------------------------------------------------------------
        #region Events
        public void OnProcessEvent(object me, string name, object sender, object param)
        {
            //passe aux contextes des vues enfants
            Panel p = this.viewGrid as Panel;
            if (p.Children.Count > 0)
            {
                foreach (Control o in p.Children.OfType<Control>())
                {
                    if (o != null && o.DataContext is ModelBase)
                    {
                        if (o.DataContext is IEventHandler)
                            (o.DataContext as IEventHandler).OnProcessEvent(this, name, sender, param);
                    }
                }
            }

            //passe aux vues enfants
            ArduinoAdmin.Lib.EventHandler.OnProcessControlEvent(this, this, name, sender, param);
        }
        #endregion
    }
}
