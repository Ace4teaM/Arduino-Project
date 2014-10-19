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

namespace ArduinoAdmin.Equipements
{
    /// <summary>
    /// Logique d'interaction pour Server.xaml
    /// </summary>
    public partial class Server : UserControl
    {
        public Server(Equipements.Model.Server context)
        {
            InitializeComponent();
            this.DataContext = context;
        }
    }
}
