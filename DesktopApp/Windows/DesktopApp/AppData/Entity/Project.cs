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
using System.IO;
using System.Runtime.Serialization;
using System.Xml;

namespace AppData.Entity
{
    /// <summary>
    /// Implémente la définition de l'entité
    /// </summary>
   [Serializable]

    public partial class Project : IEntity, ISerializable, IEntitySerializable    {
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
         
          public string EntityName { get{ return "Project"; } }

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

       #region ISerializable
        // Implement this method to serialize data. The method is called on serialization.
        public void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            info.AddValue("name", name, typeof(String));
                 }
       #endregion // ISerializable
       
       #region Serialization
       public void ReadBinary(BinaryReader reader)
       {
          // Properties
          name =  reader.ReadString();
       
          // ArduinoServer
          {
             int size = reader.ReadInt32();
             if (size > 0)
             {
                 this.ArduinoServer = new Collection<ArduinoServer>();
                 for(int i=0;i<size;i++){
                     ArduinoServer o = new ArduinoServer();
                     o.ReadBinary(reader);
                     this.AddArduinoServer(o);
                 }
             }
             else
             {
                 this.ArduinoServer = new Collection<ArduinoServer>();
             }
          }
          // DisplayContent
          {
             int size = reader.ReadInt32();
             if (size > 0)
             {
                 this.DisplayContent = new Collection<DisplayContent>();
                 for(int i=0;i<size;i++){
                     DisplayContent o = new DisplayContent();
                     o.ReadBinary(reader);
                     this.AddDisplayContent(o);
                 }
             }
             else
             {
                 this.DisplayContent = new Collection<DisplayContent>();
             }
          }
       }
       
       public void WriteBinary(BinaryWriter writer)
       {
          // Properties
          writer.Write(name);
       
          // ArduinoServer
          writer.Write(this.arduinoserver.Count);
          if (this.arduinoserver.Count > 0)
          {
              foreach (var col in this.arduinoserver)
                  col.WriteBinary(writer);
          }
          // DisplayContent
          writer.Write(this.displaycontent.Count);
          if (this.displaycontent.Count > 0)
          {
              foreach (var col in this.displaycontent)
                  col.WriteBinary(writer);
          }}
       
       
       /// <summary>
       /// Convertie l'instance en élément XML
       /// </summary>
       /// <param name="parent">Élément parent reçevant le nouveau noeud</param>
       /// <returns>Text XML du document</returns>
       public string ToXml(XmlElement parent)
       {
          XmlElement curMember = null;
          XmlDocument doc = null;
          // Element parent ?
          if (parent != null)
          {
              doc = parent.OwnerDocument;
          }
          else
          {
              doc = new XmlDocument();
              parent = doc.CreateElement("root");
              doc.AppendChild(parent);
          }
       
          //Ecrit au format XML
          XmlElement cur = doc.CreateElement("Project");
          parent.AppendChild(cur);
              
          //
          // Fields
          //
          
       		// Assigne le membre Name
          if (name != null)
          {
              curMember = doc.CreateElement("Name");
              curMember.AppendChild(doc.CreateTextNode(name.ToString()));
              cur.AppendChild(curMember);
          }
          
          //
          // Aggregations
          //
       
          // ArduinoServer
          {
             curMember = doc.CreateElement("ArduinoServer");
             if (this.arduinoserver.Count > 0)
             {
                 foreach (var col in this.arduinoserver)
                     col.ToXml(curMember);
             }
             cur.AppendChild(curMember);
          }
       
          // DisplayContent
          {
             curMember = doc.CreateElement("DisplayContent");
             if (this.displaycontent.Count > 0)
             {
                 foreach (var col in this.displaycontent)
                     col.ToXml(curMember);
             }
             cur.AppendChild(curMember);
          }
       
          parent.AppendChild(cur);
          return doc.InnerXml;
       }
       
       /// <summary>
       /// Initialise l'instance avec les données de l'élément XML
       /// </summary>
       /// <param name="element">Élément contenant les information sur l'objet</param>
       /// <remarks>Seuls les éléments existants dans le noeud Xml son importés dans l'objet</remarks>
       public void FromXml(XmlElement element)
       {
          foreach (XmlElement m in element.ChildNodes)
          {
              string property_value = m.InnerText.Trim();
              // charge les paramètres
              switch (m.Name)
              {
                //
                // Fields
                //
       
                // Assigne le membre Name
                case "Name":
                {
                   this.name = property_value;
                }
                break;
       
                //
                // Aggregations
                //
                
                // Assigne la collection ArduinoServer
                case "ArduinoServer":
                   {
                      foreach (XmlElement c in m.ChildNodes)
                      {
                         if("ArduinoServer" == m.Name){
                             ArduinoServer value = new ArduinoServer();
                             value.FromXml(c);
                             this.AddArduinoServer(value);
                         }
                      }
                   }
                   break;
                // Assigne la collection DisplayContent
                case "DisplayContent":
                   {
                      foreach (XmlElement c in m.ChildNodes)
                      {
                         if("DisplayContent" == m.Name){
                             DisplayContent value = new DisplayContent();
                             value.FromXml(c);
                             this.AddDisplayContent(value);
                         }
                      }
                   }
                   break;
       			}
          }
       }
       
       #endregion // Serialization


      }

}