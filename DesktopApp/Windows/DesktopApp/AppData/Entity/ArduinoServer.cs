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
using System.IO;
using System.Runtime.Serialization;
using System.Xml;

namespace AppData.Entity
{
    /// <summary>
    /// Implémente la définition de l'entité
    /// </summary>
   [Serializable]

    public partial class ArduinoServer : IEntity, ISerializable, IEntitySerializable    {
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
         
          public string EntityName { get{ return "ArduinoServer"; } }

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

       #region ISerializable
        // Implement this method to serialize data. The method is called on serialization.
        public void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            info.AddValue("token", token, typeof(String));
            info.AddValue("ipv4", ipv4, typeof(String));
                 }
       #endregion // ISerializable
       
       #region Serialization
       public void ReadBinary(BinaryReader reader)
       {
          // Properties
          token =  reader.ReadString();
          ipv4 =  reader.ReadString();
       }
       
       public void WriteBinary(BinaryWriter writer)
       {
          // Properties
          writer.Write(token);
          writer.Write(ipv4);}
       
       
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
          XmlElement cur = doc.CreateElement("ArduinoServer");
          parent.AppendChild(cur);
              
          //
          // Fields
          //
          
       		// Assigne le membre Token
          if (token != null)
          {
              curMember = doc.CreateElement("Token");
              curMember.AppendChild(doc.CreateTextNode(token.ToString()));
              cur.AppendChild(curMember);
          }
       
       		// Assigne le membre Ipv4
          if (ipv4 != null)
          {
              curMember = doc.CreateElement("Ipv4");
              curMember.AppendChild(doc.CreateTextNode(ipv4.ToString()));
              cur.AppendChild(curMember);
          }
          
          //
          // Aggregations
          //
       
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
       
                // Assigne le membre Token
                case "Token":
                {
                   this.token = property_value;
                }
                break;
                // Assigne le membre Ipv4
                case "Ipv4":
                {
                   this.ipv4 = property_value;
                }
                break;
       
                //
                // Aggregations
                //
                
       			}
          }
       }
       
       #endregion // Serialization


      }

}