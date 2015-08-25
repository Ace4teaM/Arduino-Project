/*
   Extension de la classe d'entité ArduinoServer

   !!Attention!!
   Ce code source est généré automatiquement, toutes modifications seront perdues
   
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Globalization;
using System.Reflection;
using System.Collections.ObjectModel;
using Lib;
using AppData.Format;

namespace AppData.Entity
{
    /// <summary>
    /// Implémente la définition de l'entité
    /// </summary>
    public partial class ArduinoServer    {
         #region Constructor
         public ArduinoServer(){
            // Token
            this.token = String.Empty;
            // IPv4
            this.ipv4 = String.Empty;
         }
         
         public ArduinoServer(String token, String ipv4) : this(){
            this.token = token;
            this.ipv4 = ipv4;
         }
         #endregion // Constructor

         #region State
        private EntityState entityState;
        public EntityState EntityState { get{ return entityState; } set{ entityState = value; } }

         #endregion // State
        
         #region Fields
         // Identifiant
         protected String token;
         public String Token { get{ return token; } set{ token = value; } }
         // Adresse IP
         protected String ipv4;
         public String Ipv4 { get{ return ipv4; } set{ ipv4 = value; } }
         #endregion // Fields

         #region Associations
         // 
         protected Project project;
         public virtual Project Project { get{ return project; } set{ project = value; } }
         #endregion // Associations

         #region Methods
         public override string ToString()
         {
             string result = this.GetType().Name+":"+Environment.NewLine+"-----------------------------"+Environment.NewLine;
             result += "token = " + token + Environment.NewLine;
             result += "ipv4 = " + ipv4 + Environment.NewLine;
             return result;
         }

         #endregion // Methods




      }

}