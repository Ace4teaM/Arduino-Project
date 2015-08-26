using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Lib;

namespace DesktopApp
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, IEventProcess
    {
        public MainWindow()
        {
            InitializeComponent();
            this.DataContext = new ModelView.MainWindow();
        }

        private void ProjectTreeView_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            //Affiche la vue de l'élément seléctionné...
        }

        //-----------------------------------------------------------------------------------------
        // IEventProcess
        //-----------------------------------------------------------------------------------------
        public void ProcessEvent(object from, object _this, IEvent e)
        {
            // Envoi aux vues enfants
            this.ProjectView.ProcessEvent(from, this, e);

            // Envoi au contexte
            if (this.DataContext != null && this.DataContext is IEventProcess)
                (this.DataContext as IEventProcess).ProcessEvent(from, this, e);
        }
    }
}
