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
using Lib;

namespace DesktopApp.View
{
    /// <summary>
    /// Logique d'interaction pour EditView.xaml
    /// </summary>
    public partial class EditView : Grid
    {
        // mode d'édition
        public enum EditMode
        {
            Other = 0,
            Edit,
            Insert,
            Duplicate,
            ReadOnly
        };

        public EditView()
        {
            InitializeComponent();
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

        // Ajoute un bouton à l'interface
        public Button AddButton(string libelle, RoutedEventHandler clickEvent)
        {
            Button btn = new Button();
            btn.Content = libelle;
            btn.Click += clickEvent;
            AddElement(btn);
            return btn;
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
    }
}
