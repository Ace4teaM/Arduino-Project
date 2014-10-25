using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media.Imaging;
using ArduinoAdmin.Fenetres;
using ArduinoAdmin.Lib;
using ArduinoAdmin.Model;
namespace ArduinoAdmin.VueModels.Synoptique
{
    public class Switch : Objet
    {
        public Switch() : base()
        {
            OnStateImage = ArduinoAdmin.VueModels.Synoptique.Objet.LoadBitmapFromResource("Ressources/Equipements/switch_on.png");
            OffStateImage = ArduinoAdmin.VueModels.Synoptique.Objet.LoadBitmapFromResource("Ressources/Equipements/switch_off.png");
            ImageSource = OffStateImage;
            this.state = false;
            Click = new Action(OnClick);
            RightClick = new Action(OnRightClick);
            this.Width = this.Height = 30;
        }
        private void OnClick()
        {
            this.state = !this.state;
            this.State = state;
            Console.WriteLine("Set state to " + this.state.ToString());
        }
        private void OnRightClick()
        {
            //initialise le dialogue
            EditWnd wnd = new EditWnd("Propriétés du switch");
            wnd.DataContext = this;
            wnd.AddInput("Etat", "State");
            wnd.AddInput("Numéro PIN Entrée", "StatePin");
            wnd.AddInput("Numéro PIN Sortie", "PushPin");
            wnd.Owner = Application.Current.MainWindow;
            //affiche le dialogue
            wnd.ShowDialog();
        }
        public bool? state;
        public bool? State
        {
            get
            {
                //envoi la commande
                if (this.StatePin != -1 && this.Equipement != null && this.Equipement.Serveur != null)
                {
                    Console.WriteLine("envoi la commande DIN...");
                    Message message = new Message(Message.MessageType.Command);
                    message.Parameters.Add("CodeCmd", "DIN");
                    message.Parameters.Add("PinNum", StatePin.ToString());
                    this.Equipement.Serveur.SendMessage(message);
                }
                //lit le retour
                //..
                //actualise l'état de l'objet
                //state = value;
                return state;
            }
            set
            {
                //envoi la commande
                if (this.PushPin != -1 && this.Equipement != null && this.Equipement.Serveur != null)
                {
                    Console.WriteLine("envoi la commande DOUT...");
                    Message message = new Message(Message.MessageType.Command);
                    message.Parameters.Add("CodeCmd", "DOUT");
                    message.Parameters.Add("PinNum", PushPin.ToString());
                    if (value == true)
                    {
                        message.Parameters.Add("Value", "1");
                        this.ImageSource = this.OnStateImage;
                    }
                    else if (value == false)
                    {
                        message.Parameters.Add("Value", "0");
                        this.ImageSource = this.OffStateImage;
                    }
                    this.Equipement.Serveur.SendMessage(message);
                }
            }
        }

        //config
        public int StatePin { get; set; }
        public int PushPin { get; set; }
        //GFX
        public BitmapImage OnStateImage { get; set; }
        public BitmapImage OffStateImage { get; set; }
    }
}
