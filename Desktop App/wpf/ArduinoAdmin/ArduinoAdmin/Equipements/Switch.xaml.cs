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
using ArduinoAdmin.Equipements;

namespace ArduinoAdmin.Equipements
{
    /// <summary>
    /// Logique d'interaction pour Switch.xaml
    /// </summary>
    public partial class Switch : UserControl
    {
        public Switch(Equipements.Model.Switch context)
        {
            InitializeComponent();
            this.DataContext = context;
        }

        private void UserControl_MouseDown(object sender, MouseButtonEventArgs e)
        {
            Model.Switch switchCtx = this.DataContext as Model.Switch;
            if (switchCtx!=null)
            {
                switchCtx.Push();
            }
        }
    }
}
