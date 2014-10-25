using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;
using ArduinoAdmin.Lib;

namespace ArduinoAdmin.VueModels.Synoptique
{
    public class InternalLed : Objet
    {
        public InternalLed()
            : base()
        {
            OnStateImage = ArduinoAdmin.VueModels.Synoptique.Objet.LoadBitmapFromResource("Ressources/Equipements/rec_on.png");
            OffStateImage = ArduinoAdmin.VueModels.Synoptique.Objet.LoadBitmapFromResource("Ressources/Equipements/rec_off.png");
        }
        public bool? state;
        public bool? State
        {
            get
            {
                return state;
            }
            set
            {
                //envoi la commande
                if (this.Equipement != null && this.Equipement.Serveur != null)
                {
                    Message message = new Message(Message.MessageType.Command);
                    if (value == true)
                        message.Parameters.Add("CodeCmd", "LEDH");
                    else if (value == false)
                        message.Parameters.Add("CodeCmd", "LEDL");
                    this.Equipement.Serveur.SendMessage(message);
                }
            }
        }
        public BitmapImage OnStateImage { get; set; }
        public BitmapImage OffStateImage { get; set; }
    }
}
