using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
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

namespace ArduinoAdmin.Vues
{
    /// <summary>
    /// Logique d'interaction pour Synoptique.xaml
    /// </summary>
    public partial class Synoptique : UserControl
    {
        public Synoptique()
        {
            InitializeComponent();
            //ajoute le server
            Equipements.Model.Server server = new Equipements.Model.Server();
            server.Ip = new IPAddress(new byte[] { 192, 168, 1, 30 });
            AddEquipement(new Equipements.Server(server), 150, 50);
            //ajoute le switch LED
            Equipements.Model.Switch switch1 = new Equipements.Model.Switch(server,13);
            AddEquipement(new Equipements.Switch(switch1), 10, 50);
            //ajoute le switch test
            Equipements.Model.Switch switch2 = new Equipements.Model.Switch(server, 22);
            AddEquipement(new Equipements.Switch(switch2), 10, 100);
        }

        public void AddEquipement(UserControl ctrl, double x, double y)
        {
            ctrl.SetValue(Canvas.LeftProperty, x);
            ctrl.SetValue(Canvas.TopProperty, y);
            this.viewport.Children.Add(ctrl);
        }
    }
}
