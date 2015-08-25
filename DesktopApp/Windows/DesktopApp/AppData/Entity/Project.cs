/*
   Extension de la classe d'entité Project

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
    public partial class Project    {
         #region Constructor
         public Project(){

            // ArduinoServer
            this.arduinoserver = new Collection<ArduinoServer>();
            // DisplayContent
            this.displaycontent = new Collection<DisplayContent>();
            // Name
            this.name = String.Empty;
         }
         
         public Project(String name) : this(){
            this.name = name;
         }
         #endregion // Constructor

         #region State
        private EntityState entityState;
        public EntityState EntityState { get{ return entityState; } set{ entityState = value; } }

         #endregion // State
        
         #region Fields
         // Nom du projet
         protected String name;
         public String Name { get{ return name; } set{ name = value; } }
         #endregion // Fields

         #region Associations
         // 
         protected Collection<ArduinoServer> arduinoserver;
         public virtual Collection<ArduinoServer> ArduinoServer { get{ return arduinoserver; } set{ arduinoserver = value; } }
         public void AddArduinoServer(ArduinoServer obj){
            obj.Project = this;
            ArduinoServer.Add(obj);
         }
         
         public void RemoveArduinoServer(ArduinoServer obj){
            obj.Project = null;
            ArduinoServer.Remove(obj);
         }
         // 
         protected Collection<DisplayContent> displaycontent;
         public virtual Collection<DisplayContent> DisplayContent { get{ return displaycontent; } set{ displaycontent = value; } }
         public void AddDisplayContent(DisplayContent obj){
            obj.Project = this;
            DisplayContent.Add(obj);
         }
         
         public void RemoveDisplayContent(DisplayContent obj){
            obj.Project = null;
            DisplayContent.Remove(obj);
         }
         #endregion // Associations

         #region Methods
         public override string ToString()
         {
             string result = this.GetType().Name+":"+Environment.NewLine+"-----------------------------"+Environment.NewLine;
             result += "name = " + name + Environment.NewLine;
             return result;
         }

         #endregion // Methods




      }

}