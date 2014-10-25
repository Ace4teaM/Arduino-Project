/*
   Vue d'édition de la classe Etat

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
    /// Logique d'interaction pour Edit_Etat.xaml
    /// </summary>
    public partial class Edit_Etat : UserControl
    {
        public Edit_Etat()
        {
            InitializeComponent();
            Mode = EditWnd.EditMode.Other;
        }

        public Edit_Etat(EditWnd.EditMode mode)
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
        public static readonly DependencyProperty EnabledItemsProperty = DependencyProperty.Register("EnabledItems", typeof(string), typeof(Edit_Etat), new PropertyMetadata(string.Empty, EnabledItemsChanged));
        public string EnabledItems
        {
            get { return (string)base.GetValue(EnabledItemsProperty); }
            set { base.SetValue(EnabledItemsProperty, value); }
        }

        private static void EnabledItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_Etat;

             string[] _args = me.EnabledItems.Split(new char[]{','},StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_Etat_Id.IsEnabled = false;
             me.itemGroup_Nom.IsEnabled = false;
             me.itemGroup_Valeur.IsEnabled = false;             

             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "Etat_Id":
                         me.itemGroup_Etat_Id.IsEnabled = true;
                         break;
                     case "Nom":
                         me.itemGroup_Nom.IsEnabled = true;
                         break;
                     case "Valeur":
                         me.itemGroup_Valeur.IsEnabled = true;
                         break;
               }
            }
        }
        #endregion
        #region VisibleItems
        /// <summary>
        /// Définit les éléments visibles du dialogue
        /// </summary>
        public static readonly DependencyProperty VisibleItemsProperty = DependencyProperty.Register("VisibleItems", typeof(string), typeof(Edit_Etat), new PropertyMetadata(string.Empty, VisibleItemsChanged));
        public string VisibleItems
        {
            get { return (string)base.GetValue(VisibleItemsProperty); }
            set { base.SetValue(VisibleItemsProperty, value); }
        }

        private static void VisibleItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_Etat;

             string[] _args = me.VisibleItems.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_Etat_Id.Visibility = Visibility.Collapsed;
             me.itemGroup_Nom.Visibility = Visibility.Collapsed;
             me.itemGroup_Valeur.Visibility = Visibility.Collapsed;             


             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "Etat_Id":
                         me.itemGroup_Etat_Id.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Etat_Id);
                         me.itemGroups.Children.Add(me.itemGroup_Etat_Id);
                         break;
                     case "Nom":
                         me.itemGroup_Nom.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Nom);
                         me.itemGroups.Children.Add(me.itemGroup_Nom);
                         break;
                     case "Valeur":
                         me.itemGroup_Valeur.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Valeur);
                         me.itemGroups.Children.Add(me.itemGroup_Valeur);
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
                this.itemGroup_Etat_Id.Visibility = Visibility.Visible;
                this.itemGroup_Nom.Visibility = Visibility.Visible;
                this.itemGroup_Valeur.Visibility = Visibility.Visible;                

                // active / desactive l'édition
                switch (value as EditWnd.EditMode?)
                {
                    case EditWnd.EditMode.ReadOnly:
                        this.itemGroup_Etat_Id.IsEnabled = false;
                        this.itemGroup_Nom.IsEnabled = false;
                        this.itemGroup_Valeur.IsEnabled = false;
                      break;
                    default:
                        this.itemGroup_Etat_Id.IsEnabled = false; //<< par defaut les identifiants ne sont pas editable
                        this.itemGroup_Nom.IsEnabled = true;
                        this.itemGroup_Valeur.IsEnabled = true;
                      break;
                }
            }
        }
        #endregion
        #endregion
    }
}