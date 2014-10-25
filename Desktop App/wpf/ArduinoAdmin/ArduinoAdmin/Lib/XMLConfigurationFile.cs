using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace PrmNep.Lib
{
    public class XMLConfigurationFile: IConfigurable
    {
        private XmlDocument doc;
        private XmlElement curSection;

        public XMLConfigurationFile()
        {
            doc = new XmlDocument();
        }

        public bool IsInitialised()
        {
            return (doc!=null && doc.DocumentElement != null);
        }

        public bool Load(string fileName)
        {
            try
            {
                string content = File.ReadAllText(fileName);
                doc.LoadXml(content);
                return true;
            }
            catch (Exception)
            {
            }
            curSection = doc.DocumentElement;
            return false;
        }

        public void SetSection(string name)
        {
            //XmlElement section = doc.GetElementById(name); // requiere un Doctype
            XmlElement section = doc.SelectSingleNode("//Section[@id='" + name + "']") as XmlElement;
            
            if (section == null)
            {
                section = doc.CreateElement("Section");
                section.SetAttribute("id", name);
                doc.DocumentElement.AppendChild(section);
            }
            this.curSection = section;
        }

        public void Create()
        {
            doc.AppendChild(doc.CreateXmlDeclaration("1.0", "UTF-8", null));
            doc.AppendChild(doc.CreateElement("data") );
            curSection = doc.DocumentElement;
        }

        public void Save(string fileName)
        {
            doc.Save(fileName);
        }

        public string ReadVar(string name)
        {
            XmlNodeList list = this.curSection.GetElementsByTagName(name);
            if (list.Count < 1)
                return String.Empty;
            return list[0].InnerText.Trim();
        }

        public string WriteVar(string name, string value)
        {
            XmlNodeList list = this.curSection.GetElementsByTagName(name);
            if (list.Count < 1)
            {
                XmlElement el = doc.CreateElement(name);
                this.curSection.AppendChild(el);
                el.AppendChild(doc.CreateTextNode(value));
                return value;
            }

            foreach (XmlNode child in list[0].ChildNodes)
                list[0].RemoveChild(child);
            list[0].AppendChild(doc.CreateTextNode(value));
            return value;
        }

        public List<string> ListVar()
        {
            List<string> list = new List<string>();
            foreach (XmlElement e in this.curSection.ChildNodes.OfType<XmlElement>())
            {
                list.Add(e.Name);
            }
            return list;
        }

        // Methodes aditionnelles

        public string CreateVar(string name, string defaultValue, string libelle, string description)
        {
            XmlNodeList list = this.curSection.GetElementsByTagName(name);
            XmlElement el;
            if (list.Count < 1)
            {
                el = doc.CreateElement(name);
                this.curSection.AppendChild(el);
                el.AppendChild(doc.CreateTextNode(defaultValue));
            }
            else
            {
                el = list[0] as XmlElement;
            }

            el.SetAttribute("libelle", libelle);
            el.SetAttribute("description", description);

            return defaultValue;
        }

    }
}
