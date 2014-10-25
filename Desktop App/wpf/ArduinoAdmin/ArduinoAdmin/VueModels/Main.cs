using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using ArduinoAdmin.Lib;

namespace ArduinoAdmin.VueModels
{
    public class Main : ModelBase, IEventHandler
    {
        //-----------------------------------------------------------------------------------------
        // Constructeur
        //-----------------------------------------------------------------------------------------
        public Main()
        {
            var x = (from p in app.bdd.Serveur select p);
        }

        //-----------------------------------------------------------------------------------------
        // Membres
        //-----------------------------------------------------------------------------------------
        App app = (App)Application.Current;
        
        //-----------------------------------------------------------------------------------------
        // Données
        //-----------------------------------------------------------------------------------------
        #region Data
        #endregion

        //-----------------------------------------------------------------------------------------
        // Proprietes
        //-----------------------------------------------------------------------------------------
        #region Properties
        #region FieldBrush
        public System.Windows.Media.Brush FieldBrush
        {
            get
            {
                return System.Windows.Media.Brushes.AliceBlue;
            }
        }
        #endregion
        #endregion

        //-----------------------------------------------------------------------------------------
        // Commandes
        //-----------------------------------------------------------------------------------------
        #region Commands
        #region Exit
        // Sauvegarde les modifications
        private ICommand exitCmd;
        public ICommand ExitCmd
        {
            get
            {
                /*if (this.exitCmd == null)
                    this.exitCmd = new DelegateCommand(() => this.app.Quit());
                */
                return this.exitCmd;
            }
        }
        #endregion
        #endregion//Commands

        //-----------------------------------------------------------------------------------------
        // Evénements
        // Réceptionne les événements "utilisateur" provenant des autres fenêtres puis agit en conséquence.
        //-----------------------------------------------------------------------------------------
        #region Events
        public void OnProcessEvent(object me, string name, object sender, object param)
        {
            //passe aux contextes enfants
            ArduinoAdmin.Lib.EventHandler.OnProcessModelEvent(this, this, name, sender, param);
        }
        #endregion
    }
}
