/*
   Vue d'édition de la classe Serveur

   !!Attention!!
   Ce code source est généré automatiquement, toutes modifications sera perdue
   
*/

using System;
using System.Windows;
using System.Windows.Controls;
using ArduinoAdmin.Fenetres;
namespace ArduinoAdmin.Vues
{
    /// <summary>
    /// Logique d'interaction pour Edit_Serveur.xaml
    /// </summary>
    public partial class Edit_Serveur : UserControl
    {
        public Edit_Serveur()
        {
            InitializeComponent();
            Mode = EditWnd.EditMode.Other;
        }

        public Edit_Serveur(EditWnd.EditMode mode)
            : this()
        {
            Mode = mode;
        }

        //-----------------------------------------------------------------------------------------
        // Proprietes
        //-----------------------------------------------------------------------------------------
        #region Properties
        #region EnabledItems
        /// <summary>
        /// Définit les éléments actifs du dialogue
        /// </summary>
        public static readonly DependencyProperty EnabledItemsProperty = DependencyProperty.Register("EnabledItems", typeof(string), typeof(Edit_Serveur), new PropertyMetadata(string.Empty, EnabledItemsChanged));
        public string EnabledItems
        {
            get { return (string)base.GetValue(EnabledItemsProperty); }
            set { base.SetValue(EnabledItemsProperty, value); }
        }

        private static void EnabledItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_Serveur;

             string[] _args = me.EnabledItems.Split(new char[]{','},StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_Serveur_Id.IsEnabled = false;
             me.itemGroup_AdressePhysique.IsEnabled = false;
             me.itemGroup_Jeton.IsEnabled = false;
             me.itemGroup_AdresseIP.IsEnabled = false;             

             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "Serveur_Id":
                         me.itemGroup_Serveur_Id.IsEnabled = true;
                         break;
                     case "AdressePhysique":
                         me.itemGroup_AdressePhysique.IsEnabled = true;
                         break;
                     case "Jeton":
                         me.itemGroup_Jeton.IsEnabled = true;
                         break;
                     case "AdresseIP":
                         me.itemGroup_AdresseIP.IsEnabled = true;
                         break;
               }
            }
        }
        #endregion
        #region VisibleItems
        /// <summary>
        /// Définit les éléments visibles du dialogue
        /// </summary>
        public static readonly DependencyProperty VisibleItemsProperty = DependencyProperty.Register("VisibleItems", typeof(string), typeof(Edit_Serveur), new PropertyMetadata(string.Empty, VisibleItemsChanged));
        public string VisibleItems
        {
            get { return (string)base.GetValue(VisibleItemsProperty); }
            set { base.SetValue(VisibleItemsProperty, value); }
        }

        private static void VisibleItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_Serveur;

             string[] _args = me.VisibleItems.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_Serveur_Id.Visibility = Visibility.Collapsed;
             me.itemGroup_AdressePhysique.Visibility = Visibility.Collapsed;
             me.itemGroup_Jeton.Visibility = Visibility.Collapsed;
             me.itemGroup_AdresseIP.Visibility = Visibility.Collapsed;             


             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "Serveur_Id":
                         me.itemGroup_Serveur_Id.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Serveur_Id);
                         me.itemGroups.Children.Add(me.itemGroup_Serveur_Id);
                         break;
                     case "AdressePhysique":
                         me.itemGroup_AdressePhysique.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_AdressePhysique);
                         me.itemGroups.Children.Add(me.itemGroup_AdressePhysique);
                         break;
                     case "Jeton":
                         me.itemGroup_Jeton.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Jeton);
                         me.itemGroups.Children.Add(me.itemGroup_Jeton);
                         break;
                     case "AdresseIP":
                         me.itemGroup_AdresseIP.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_AdresseIP);
                         me.itemGroups.Children.Add(me.itemGroup_AdresseIP);
                         break;
              }
            }
        }
        #endregion
        #region EditMode
        /// <summary>
        /// Indique le mode d'édition de la fenêtre
        /// </summary>
        /// <remarks>
        /// Le mode permet de verrouiller ou non les champs en lecture seules
        /// </remarks>
        private EditWnd.EditMode editMode;
        public EditWnd.EditMode Mode
        {
            get { return editMode; }
            set {
               this.editMode = value;
               
                // rend les éléments visibles
                this.itemGroup_Serveur_Id.Visibility = Visibility.Visible;
                this.itemGroup_AdressePhysique.Visibility = Visibility.Visible;
                this.itemGroup_Jeton.Visibility = Visibility.Visible;
                this.itemGroup_AdresseIP.Visibility = Visibility.Visible;                

                // active / desactive l'édition
                switch (value as EditWnd.EditMode?)
                {
                    case EditWnd.EditMode.ReadOnly:
                        this.itemGroup_Serveur_Id.IsEnabled = false;
                        this.itemGroup_AdressePhysique.IsEnabled = false;
                        this.itemGroup_Jeton.IsEnabled = false;
                        this.itemGroup_AdresseIP.IsEnabled = false;
                      break;
                    default:
                        this.itemGroup_Serveur_Id.IsEnabled = false; //<< par defaut les identifiants ne sont pas editable
                        this.itemGroup_AdressePhysique.IsEnabled = true;
                        this.itemGroup_Jeton.IsEnabled = true;
                        this.itemGroup_AdresseIP.IsEnabled = true;
                      break;
                }
            }
        }
        #endregion
        #endregion
    }
}