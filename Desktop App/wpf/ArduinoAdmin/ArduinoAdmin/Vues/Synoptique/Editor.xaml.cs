using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ArduinoAdmin.Vues.Synoptique
{
    /// <summary>
    /// Logique d'interaction pour Editor.xaml
    /// </summary>
    public partial class Editor : UserControl
    {
        public Editor()
        {
            InitializeComponent();

            //server
            ArduinoAdmin.Model.Serveur arduinoServ = new ArduinoAdmin.Model.Serveur();
            arduinoServ.AdresseIP = "192.168.1.29";
            arduinoServ.AdressePhysique = "7A-C4-0E-1D-F9-F6";
            arduinoServ.Jeton = "fdfssd";
            arduinoServ.ResolveIP();

            //arduino equipement
            ArduinoAdmin.Model.Equipement arduinoEquip = new ArduinoAdmin.Model.Equipement();
            arduinoEquip.Serveur = arduinoServ;
            arduinoEquip.Nom = "My Arduino";
            arduinoEquip.Description = "Arduino de test";
            arduinoEquip.Px = 10;
            arduinoEquip.Py = 10;
            arduinoEquip.Pz = 0;

            //ajoute l'objet server
            ArduinoAdmin.VueModels.Synoptique.Objet serveur = new VueModels.Synoptique.Objet();
            serveur.Equipement = arduinoEquip;
            serveur.Name = "Arduino 1";
            serveur.Width = 150;
            serveur.Height = 90;
            serveur.Left = 50;
            serveur.Top = 100;
            serveur.ImageSource = ArduinoAdmin.VueModels.Synoptique.Objet.LoadBitmapFromResource("Ressources/Equipements/arduino.png");
            AddEquipement(serveur);

            //ajoute l'objet interupteur de la led interne
            ArduinoAdmin.VueModels.Synoptique.Switch pin1 = new VueModels.Synoptique.Switch();
            pin1.Equipement = arduinoEquip;
            pin1.Name = "Led Interne";
            pin1.PushPin = 13;
            pin1.StatePin = -1;
            pin1.Left = 0;
            pin1.Top = 0;
            AddEquipement(pin1);

            //ajoute l'objet interupteur des Led
            int[] pin = new int[] { 22, 26, 30, 34 };
            for (int i = 0; i < pin.Length; i++)
            {
                ArduinoAdmin.VueModels.Synoptique.Switch led1 = new VueModels.Synoptique.Switch();
                led1.Equipement = arduinoEquip;
                led1.Name = "Led " + (i + 1);
                led1.PushPin = pin[i];
                led1.StatePin = -1;
                led1.Left = 100 + (i * 100);
                led1.Top = 0;
                AddEquipement(led1);
            }
        }

        public void AddEquipement(ArduinoAdmin.VueModels.Synoptique.Objet obj)
        {
            ArduinoAdmin.Vues.Synoptique.Objet objVue = new ArduinoAdmin.Vues.Synoptique.Objet();
            objVue.DataContext = obj;
            objVue.SetValue(Canvas.LeftProperty, obj.Left);
            objVue.SetValue(Canvas.TopProperty, obj.Top);
            this.viewport.Children.Add(objVue);
        }
    }
}
