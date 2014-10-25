using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Threading;
using System.Windows;
using System.Windows.Markup;
using ArduinoAdmin.Model;

namespace ArduinoAdmin
{
    /// <summary>
    /// Logique d'interaction pour App.xaml
    /// </summary>
    public partial class App : Application
    {
        public arduinoEntities1 bdd = new arduinoEntities1();

        //-----------------------------------------------------------------------------------------
        // Proprietes
        //-----------------------------------------------------------------------------------------
        #region Properties
        #region AppPath
        public string AppPath { get; set; }
        #endregion
        #endregion

        //-----------------------------------------------------------------------------------------
        // Application Méthodes
        //-----------------------------------------------------------------------------------------
        #region AppMethods
        protected override void OnStartup(StartupEventArgs e)
        {
            //ne pas fermer automatiquement l'application tant que la fenêtre principale n'est pas initialisée
            Current.ShutdownMode = ShutdownMode.OnExplicitShutdown;

            // initialise la culture sur Francaise
            Thread.CurrentThread.CurrentCulture = new CultureInfo("fr-FR"); ;
            Thread.CurrentThread.CurrentUICulture = new CultureInfo("fr-FR"); ;

            FrameworkElement.LanguageProperty.OverrideMetadata(
                typeof(FrameworkElement),
                new FrameworkPropertyMetadata(XmlLanguage.GetLanguage(CultureInfo.CurrentCulture.IetfLanguageTag))
            );

            // obtient le chemin d'accès à l'application
            AppPath = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);

            //
            // Initialise la fenetre principale
            //
            Current.ShutdownMode = ShutdownMode.OnMainWindowClose;
            this.MainWindow = new MainWindow();
            this.MainWindow.ShowDialog();

            //
            // appelle la fonction de base
            //
            base.OnStartup(e);
        }
        protected override void OnExit(ExitEventArgs e)
        {
            base.OnExit(e);
        }
        #endregion
        #region Errors
        //traduit un message d'erreur provenant de l'application
        public static string TranslateAppErrorCode(string msg)
        {
            switch (msg)
            {
                //Validation
                case "MIN_MAX_OVERFLOW_AJUSTED":
                    return "La valeur entrée dépasse la plage min/max autorisée. La valeur a été ajustée à la limite la plus proche.";
                case "NOT_NULL_RESTRICTION":
                    return "Le champ doit être spécifié";
                case "INVALID_FORMAT":
                    return "Format invalide";
                case "INVALID_BOOL_FORMAT":
                    return "Le format ne correspond pas à un booléen.\nVeuillez spécifier '1' (vrai) ou '0' (faux)";
                case "INVALID_INTEGER_FORMAT":
                    return "Le format ne correspond pas à un entier.\nVeuillez spécifier un nombre supérieur ou égale à 0";
                case "INVALID_MAIL_FORMAT":
                    return "Le format ne correspond pas à une adresse électronique.\nVeuillez spécifier une chaine au format suivant 'prefixe@domain.ext'";
                case "INVALID_NAME_FORMAT":
                    return "Le format n'est pas valide.\nVeuillez spécifier une chaine contenant uniquement des caractères aplhanumériques et/ou l'un des caractères suivant: '_', '-' ";
                case "INVALID_NOTEMPTY_FORMAT":
                    return "La chaine ne peut pas être vide";
                case "INVALID_NUMERIC_FORMAT":
                    return "Le format ne correspond pas à un nombre réel ou entier.\nVeuillez spécifier un nombre supérieur ou égale à 0";
                case "INVALID_STRINGPARAM_FORMAT":
                    return "Le format ne correspond pas à une chaine de paramètres.\nVeuillez spécifier une chaine au format suivant 'Nom=Valeur;[...]'";
                case "INVALID_PREFIXEPARAM_FORMAT":
                    return "Le format ne correspond pas à un préfixe de paramètre.\nVeuillez spécifier une chaine contenant uniquement des caractères aplhanumériques et/ou l'un des caractères suivant: '_', '-', '.'";
                //APP
                case "APP_PARAM_NAME_MUST_BE_DIFFERENT_TO_PREFIXE":
                    return "Le nom de paramètre doit être différent du prefixe.\nAjoutez votre nom à la suite du préfixe ou remplacez le par un autre.";
                case "APP_TYPEEQUIP_MUST_SPECIFY_PARAM_PREFIX":
                    return "Aucun préfixe de paramètres spécifié pour ce type d'équipement.\nVeuillez en définir un en premier.";
                case "APP_RECETTE_MUST_SPECIFY_PARAM_PREFIX":
                    return "Aucun préfixe de paramètres spécifié pour cette recette.\nVeuillez en définir un en premier.";
                case "APP_PHASE_MUST_SPECIFY_PARAM_PREFIX":
                    return "Aucun préfixe de paramètres spécifié pour cette phase.\nVeuillez en définir un dans la recette associée.";
                case "APP_PF_NO_ADDITIONAL_ARTICLE_TO_INSERT":
                    return "Aucun article supplémentaire ne peut être ajouté.\nTous les articles du catalogue sont déjà présents.";
                //Simulation OF
                case "OF_SIMULATION_UPDATEPARAM":
                    return "Mise à jour du paramètre {0} = {1}";
                case "OF_SIMULATION_END_OF_OPERATION":
                    return "Fin d'opération";
                case "OF_SIMULATION_START_OF_OPERATION":
                    return "Début d'opération";
                case "OF_SIMULATION_END":
                    return "Fin de simulation";
                case "OF_SIMULATION_START":
                    return "Début de simulation. {0} opérations durant {1} ms";
                //Defaut
                default:
                    return msg;
            }
        }

        //traduit un message d'erreur provenant d'une requete SQL
        public static string TranslateSqlErrorCode(string msg)
        {
            switch (msg)
            {
                // Process
                case "OP_ALREADY_EXISTS":
                    return "L’ordre d’opération existe déjà";
                case "OP_NOT_FOUND":
                    return "L’opération est introuvable";
                // Params
                case "PARAM_NOT_FOUND":
                    return "Nom de paramètre introuvable";
                case "PARAM_VERROUILLE":
                    return "Paramètre verrouillé contre la  suppression";
                case "PARAM_ALREADY_EXISTS":
                    return "Nom de paramètre existant";
                case "PARAM_PREFIXES_MUST_BE_DIFFERENT":
                    return "Les préfixes de paramètres doivent être différents";
                case "PARAM_PREFIX_ALREADY_USED":
                    return "Ce préfixe est déjà utilisé par d’autres paramètres. Merci de choisir un autre préfixe ou modifier les paramètres existants.";
                case "PARAM_CTRL_MIN_MAX":
                    return "La valeur ne répond pas aux critères de validation min/max";
                case "PARAM_CTRL_DATATYPE":
                    return "La valeur ne correspond pas au type de donnée";
                case "PARAM_DOMAIN_NOT_EXISTS":
                    return "Le domaine de valeurs n’existe pas";
                case "PARAM_DOMAIN_VALUE_NOT_EXISTS":
                    return "La valeur du domaine de valeurs n’existe pas";
                case "PARAM_CTRL_DOMAIN":
                    return "La valeur ne correspond pas à l’une des valeurs autorisées par le domaine de valeurs";
                // OF
                case "OF_LOCKED_STATE":
                    return "L’état de l’ordre de fabrication ne permet pas sa modification";
                case "OF_NOT_EXISTS":
                    return "L’ordre de fabrication n’existe pas";
                case "OF_NO_FORMULATION":
                    return "L’ordre de fabrication ne contient aucune formulation";
                case "OF_FORMULATION_NOT_EXISTS":
                    return "La formulation n’existe pas";
                case "OF_PREFIXEPARAM_ALREADY_USED":
                    return "Ce préfixe existe déjà dans la liste des paramètres d’OF";
                case "OF_NOT_WAIT_STATUS":
                    return "L’ordre de fabrication n’est pas en attente d’exécution";
                case "OF_NOT_WORK":
                    return "L’ordre de fabrication n’est pas en cours d’exécution";
                case "OF_PARAMLIST_NOT_FOUND":
                    return "La liste de paramètres n’existe pas pour cet OF";
                case "OF_ARCHIVE_PARAMLIST_NOT_FOUND":
                    return "La liste de paramètres d’archivage n’existe pas pour cet OF";
                case "OF_ALREADY_EXISTS_IN_ARCHIVE":
                    return "L’OF existe déjà dans la base de données d’archive";
                case "OF_PREFIXEPARAM_NOT_EXISTS":
                    return "Ce préfixe n’existe pas dans la liste des paramètres d’OF";
                case "OF_INVALID_ORDER":
                    return "L’ordre d’incorporation choisi est hors limite. Indiquer un ordre compris entre 0 et Max";
                // NEP
                case "NEP_RECETTE_NOT_FOUND":
                    return "Recette introuvable.\nElle a peut être été supprimée depuis un autre emplacement.";
                case "NEP_TYPEEQUIP_NOT_FOUND":
                    return "Equipement introuvable.\nIl a peut être été supprimé depuis un autre emplacement.";
                case "NEP_TYPEEQUIP_ALREADY_EXISTS":
                    return "Ce code equipement est déjà utilisé. Veuillez en indiquer un autre.";
                case "NEP_PHASE_NOT_FOUND":
                    return "Phase de lavage introuvable.\nElle a peut être été supprimée depuis un autre emplacement.";
                case "NEP_CODEEQUIP_ALREADY_USED":
                    return "Ce code équipement est déjà utilisé.";
                case "NEP_PHASE_ORDRESEQ_TOO_HIGH":
                    return "La séquence de phase ne peut pas être supperieur";
                case "NEP_PHASE_ORDRESEQ_TOO_LOW":
                    return "La séquence de phase ne peut pas être inférieur";
                case "NEP_PHASE_ORDRESEQ_EQUALE":
                    return "La séquence de phase est identique";
                case "NEP_RECETTE_EMPTY":
                    return "La recette n’est pas fonctionnelle. Elle ne contient pas de phases.";
                case "NEP_OPERATION_EXISTS":
                    return "Une opération existe déjà";
                case "NEP_OPERATION_NOT_FOUND":
                    return "L’opération est introuvable";
                case "NEP_RECETTE_EMPTY_PREFIXEPARAM":
                    return "La recette doit spécifier un préfixe de nom valide pour la liste des paramètres de phases";
                case "NEP_RECETTE_PREFIXES_MUST_BE_DIFFERENT":
                    return "Le préfixe de paramètres de recette et le préfixe de paramètres de phase doit être différent";
                case "PARAM_PREFIXE_ALREADY_USED_BY_RECETTE":
                    return "Ce préfixe de paramètres est déjà utilisé par une autre recette";
                case "PARAM_PREFIXE_ALREADY_USED_BY_TYPEEQUIP":
                    return "Ce préfixe de paramètres est déjà utilisé par un autre type d’équipement";
                // Catalogues
                case "ARTICLE_SOURCE_WAITING_FOR_DEPOTAGE":
                    return "Un article est en attente de dépotage sur ce point d’entrée";
                case "ARTICLE_DEPOTAGE_NOT_FOUND":
                    return "Le point de dépotage est introuvable";
                case "EQUIP_NOT_FOUND":
                    return "L’équipement est introuvable";
                case "EQUIP_CODEEQUIP_ALREADY_USED":
                    return "Ce code équipement est déjà utilisé";
                case "ARTICLE_NOT_FOUND":
                    return "Cet article est introuvable";
                case "ARTICLE_SOURCE_ALREADY_USED":
                    return "Un article du même code est déjà associé à ce point d’entrée";
                // Produit Fini
                case "PF_CODEPF_ALREADY_EXISTS":
                    return "Ce code de produit fini est déjà utilisé";
                case "PF_RECETTE_NOT_FOUND":
                    return "La recette est introuvable";
                case "PF_INGREDIENT_ALREADY_USED":
                    return "Cet ingrédient est déjà incorporé à la recette";
                case "PF_INGREDIENT_NOT_FOUND":
                    return "Ingrédient introuvable";
                case "PF_PREFIXEPARAM_ALREADY_USED":
                    return "Ce préfixe existe déjà dans la liste des paramètres de la recette";
                case "PF_PREFIXEPARAM_NOT_EXISTS":
                    return "Ce préfixe n’existe pas dans la liste des paramètres de la recette";
                // Utilisateur
                case "USER_NOT_EXISTS":
                    return "L'Utilisateur spécifié n'existe pas";
                case "USER_PSEUDO_ALREADY_USED":
                    return "Ce nom d'utilisateur est déjà utilisé";
                case "USER_AUTORISATION_NOT_EXISTS":
                    return "L'autorisation spécifiée n'existe pas";
                case "USER_INVALID_IDENTITY":
                    return "Le nom d'utilisateur ou le mot-de-passe est invalide";
                case "USER_CODE_AUTORISATION_ALREADY_USED":
                    return "Ce code d'autorisation est déjà utilisé";
                // Autres
                case "DB_VERSION_NOT_EQUALE":
                    return "La version de la base de données cible diffère de cette base de données";
                case "DB_ARCHIVE_FROM_ARCHIVE":
                    return "L’archivage ne peut être initié depuis la base de données d’archivage";
                default:
                    //autres messages generiques retourné par la BDD
                    if (msg.IndexOf("UNIQUE KEY") != -1)
                        msg = "Une entrée avec des données similaires existe déjà.\nDétail de l'erreur:\n" + msg;
                    return msg;
            }
        }

        /// <summary>
        /// Traduit une exception en message d'erreur
        /// </summary>
        /// <param name="ex">Exception à traiter</param>
        public static string TranslateErrorCode(Exception ex)
        {
            if (ex == null)
            {
                return String.Empty;
            }

            // la première ligne contient le code erreur, les lignes suivantes, des messages complémentaires
            string code = ex.Message;
            string msg = String.Empty;
            int lineSepIdx = ex.Message.IndexOf("\r\n");
            if (lineSepIdx > 0)
            {
                code = ex.Message.Substring(0, lineSepIdx);
                msg = ex.Message.Substring(lineSepIdx + 2);
            }

            Console.WriteLine("code=" + code);
            Console.WriteLine("msg=" + msg);

            // Traduit le code
            if (ex is SqlException)
            {
                code = TranslateSqlErrorCode(code);
            }
            else if (ex is FormatException)
            {
                code = TranslateAppErrorCode(code);
            }
            else if (ex is ValidationException)
            {
                code = TranslateAppErrorCode(code);
            }
            else if (ex is ApplicationException)
            {
                code = TranslateAppErrorCode(code);
            }

            // retourne le message complet
            return code + (String.IsNullOrEmpty(msg) ? String.Empty : Environment.NewLine + msg);
        }

        /// <summary>
        /// Traite une exception retourné par l'application
        /// </summary>
        /// <param name="ex">Exception à traiter</param>
        /// <remarks>Cette fonction permet de transmettre une erreur retournée par la base de donnée ou l'application vers l'utilisateur dans une boite de dialogue.</remarks>
        public void ProcessException(Exception ex)
        {
            string msg = TranslateErrorCode(ex);
            if (ex is SqlException)
            {
                // string msg = TranslateSqlErrorCode(ex.Message);
                MessageBox.Show(msg, "Attention", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
            else if (ex is FormatException)
            {
                // string msg = TranslateAppErrorCode(ex.Message);
                MessageBox.Show(msg, "Format incorrecte", MessageBoxButton.OK, MessageBoxImage.Warning);
                //MessageBox.Show("Au moins un paramètre n'est pas valide. Merci de renseigner correctement le(s) champ(s) suivant(s):\n" + ex.Message, "Format de champ incorrecte", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
            else if (ex is ValidationException)
            {
                // string msg = TranslateAppErrorCode(ex.Message);
                MessageBox.Show(msg, "Champ incorrecte", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
            else if (ex is ApplicationException)
            {
                // string msg = TranslateAppErrorCode(ex.Message);
                MessageBox.Show(msg, "Attention", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
            else if (ex != null)
            {
                // Exception non géré
                if (MessageBox.Show(ex.Message + "\nVoulez-vous terminer l'exécution de l'application ?", "Exception non gérée", MessageBoxButton.YesNo, MessageBoxImage.Error) != MessageBoxResult.No)
                    this.Shutdown(0);
                Console.WriteLine(ex);
            }
        }
        #endregion
    }
}
