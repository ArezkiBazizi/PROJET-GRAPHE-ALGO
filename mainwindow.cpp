#include "mainwindow.h"
#include<iostream>
#include<QMessageBox>

MainWindow::MainWindow(QMainWindow* parent) : QMainWindow{parent}, d_wg{new widgetGraph(1500, 1000)}, d_wgClone{new widgetGraph(1500,1000)}, d_vue{this}, menuPruferD{new menuPruferDecode}, menuDijkstra{new menudijkstra}, menuOrd{new menuOrdonnancement}, menuS{new menuAjout}, menuSuppr{new menuSupprimer}, menuFSAPS{new class saisieFSAPS}, menuMatrice{new class saisieMatrice}
{
    d_vue.creeInterface(d_wg);

    connect(&d_vue, &vue::Quitter, this, &MainWindow::close);
    connect(&d_vue, &vue::Charger, this, &MainWindow::charge);
    connect(&d_vue, &vue::SaisieFSAPS, this, &MainWindow::saisieFSAPS);
    connect(&d_vue, &vue::SaisieMatrice, this, &MainWindow::saisieMatrice);
    connect(&d_vue, &vue::Ajout, this, &MainWindow::ajoute);
    connect(&d_vue, &vue::Suppression, this, &MainWindow::supprime);

    connect(&d_vue, &vue::AlgorithmeSelectionneDistance, this, &MainWindow::onClick_Distance);
    connect(&d_vue, &vue::AlgorithmeSelectionneRang, this, &MainWindow::onClick_Rang);
    connect(&d_vue, &vue::AlgorithmeSelectionneTarjan, this, &MainWindow::onClick_Tarjan);
    connect(&d_vue, &vue::AlgorithmeSelectionneOrdonnancement, this, &MainWindow::onClick_Ordonnancement);
    connect(&d_vue, &vue::AlgorithmeSelectionneDijkstra, this, &MainWindow::onClick_Dijkstra);
    connect(&d_vue, &vue::AlgorithmeSelectionneDantzig, this, &MainWindow::onClick_Dantzig);
    connect(&d_vue, &vue::AlgorithmeSelectionneKruskal, this, &MainWindow::onClick_Kruskal);
    connect(&d_vue, &vue::AlgorithmeSelectionnePruferEncode, this, &MainWindow::onClick_Prufer_encode);
    connect(&d_vue, &vue::AlgorithmeSelectionnePruferDecode, this, &MainWindow::onClick_Prufer_decode);

    connect(menuPruferD, &menuPruferDecode::valide, this, &MainWindow::onValiderPruferDecode);
    connect(menuDijkstra, &menudijkstra::valide, this, &MainWindow::onValiderDijkstra);
    connect(menuOrd, &menuOrdonnancement::valide, this, &MainWindow::onValiderOrdonnancement);
    connect(menuS, &menuAjout::envoieAjout, this, &MainWindow::onValiderAjout);

    connect(menuFSAPS, &saisieFSAPS::envoieSaisieFSAPS, this, &MainWindow::onValideSaisieFSAPS);
    connect(menuMatrice, &saisieMatrice::envoieSaisieMatrice, this, &MainWindow::onValideSaisieMatrice);


}

bool MainWindow::verifieDistance()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit oriente.
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
                return true;
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DISTANCE: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        else if(d_wg.verifieMatrice_NonVide())
        {
            return true;
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DISTANCE: ","Matrice vide !",QMessageBox::Ok};
            info->exec();
            return false;
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DISTANCE: ","Graphe non oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}

bool MainWindow::verifieRang()
{

    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
                return true;
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR RANG: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        else if(d_wg.verifieMatrice_NonVide())
        {
            return true;
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR RANG: ","Matrice vide !",QMessageBox::Ok};
            info->exec();
            return false;
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR RANG: ","Graphe non oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}
bool MainWindow::verifieTarjan()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
                return true;
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR TARJAN: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        else if(d_wg.verifieMatrice_NonVide())
        {
            return true;
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR TARJAN: ","Matrice vide !",QMessageBox::Ok};
            info->exec();
            return false;
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR TARJAN: ","Graphe non oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}
bool MainWindow::verifieOrdonnancement()
{
    return true; //Dans tous les cas, c'est deja verifie..
}

bool MainWindow::verifieDijkstra(int sommet_depart)
{
    //Il faut que le graphe soit oriente.
    //Il faut que fs et aps soit initialisé ou la matrice.
    //Il faut que le cout soit correct, qu'il ne contienne pas de cout < 0
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
            {
                if(sommet_depart <= 0 || sommet_depart > d_wg.getAps()[0])
                {
                    string str = std::to_string(d_wg.getAps()[0]);
                    QString s = "Le sommet saisi n'est pas valide ! Veuillez saisir un sommet compris entre 1 et ";
                    s += s.fromStdString(str);
                    auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ",s,QMessageBox::Ok};
                    info->exec();
                    return false; //Le sommet saisi n'est pas valide !
                }
                else
                {
                    if(d_wg.verifieCout_NonVide())
                    {
                        vector<vector<int>> couts = d_wg.getCouts();
                        if(couts[0][0] != d_wg.getAps()[0] || couts[0][1] != (d_wg.getFs()[0] - d_wg.getAps()[0]))
                        {
                            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Les elements presents dans le cout en ligne 0 ne correspondent pas avec le fs et aps",QMessageBox::Ok};
                            info->exec();
                            return false;//Les elements presents dans le cout ne correspondent pas avec le fs et aps
                        }
                        else
                        {
                            for(unsigned i = 1 ; i < couts.size() ; ++i)
                            {
                                for(unsigned j = 1 ; j < couts[i].size() ; ++j)
                                {
                                    if(couts[i][j] < -1)
                                    {
                                        string str = std::to_string(i);
                                        string str2 = std::to_string(j);
                                        QString s = "L'element present dans le cout en ligne ";
                                        s += s.fromStdString(str);
                                        s += " et en colonne ";
                                        s += s.fromStdString(str2);
                                        s += " est negatif ! Veuillez modifier cette valeur en positive pour utiliser Dijkstra.";
                                        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ",s,QMessageBox::Ok};
                                        info->exec();
                                        return false;//Cout negatif interdit !
                                    }
                                }
                            }
                            return true;
                        }
                    }
                    else
                    {
                        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Le cout est vide !",QMessageBox::Ok};
                        info->exec();
                        return false; //Cout vide
                    }
                }
            }
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false; //Graphe Vide - Fs & Aps
            }
        //Matrice
        }
        else
        {
            if(d_wg.verifieMatrice_NonVide())
            {
                int n = d_wg.getMatrice()[0][0];
                int m = d_wg.getMatrice()[0][1];
                if(sommet_depart <= 0 || sommet_depart > n)
                {
                    string str = std::to_string(n);
                    QString s = "Le sommet saisi n'est pas valide ! Veuillez saisir un sommet compris entre 1 et ";
                    s += s.fromStdString(str);
                    auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ",s,QMessageBox::Ok};
                    info->exec();
                    return false; //Le sommet saisi n'est pas valide !
                }
                else
                {
                    if(d_wg.verifieCout_NonVide())
                    {
                        vector<vector<int>> couts = d_wg.getCouts();
                        if(couts[0][0] != n || couts[0][1] != m)
                        {
                            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Les elements presents dans le cout en ligne 0 ne correspondent pas avec la matrice",QMessageBox::Ok};
                            info->exec();
                            return false;//Les elements presents dans le cout ne correspondent pas avec la matrice
                        }
                        else
                        {
                            for(unsigned i = 1 ; i < couts.size() ; ++i)
                            {
                                for(unsigned j = 1 ; j < couts[i].size() ; ++j)
                                {
                                    if(couts[i][j] < 0)
                                    {
                                        string str = std::to_string(i);
                                        string str2 = std::to_string(j);
                                        QString s = "L'element present dans le cout en ligne ";
                                        s += s.fromStdString(str);
                                        s += " et en colonne ";
                                        s += s.fromStdString(str2);
                                        s += " est negatif ! Veuillez modifier cette valeur en positive pour utiliser Dijkstra.";
                                        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ",s,QMessageBox::Ok};
                                        info->exec();
                                        return false;//Cout negatif interdit !
                                    }
                                }
                            }
                            return true;
                        }
                    }
                    else
                    {
                        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Le cout est vide !",QMessageBox::Ok};
                        info->exec();
                        return false; //Cout vide
                    }
                }
            }
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Matrice vide !",QMessageBox::Ok};
                info->exec();
                return false; //Graphe Vide - Matrice
            }
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DIJKSTRA: ","Graphe non oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}
bool MainWindow::verifieDantzig()
{
    //Il faut que le graphe soit oriente.
    //Il faut que le cout soit bien initialisé ou la matrice.
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
            {
                if(d_wg.verifieCout_NonVide())
                {
                    vector<vector<int>> couts = d_wg.getCouts();
                    if(couts[0][0] != d_wg.getAps()[0] || couts[0][1] != (d_wg.getFs()[0] - d_wg.getAps()[0]))
                    {
                        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","Les elements presents dans le cout en ligne 0 ne correspondent pas avec le fs et aps",QMessageBox::Ok};
                        info->exec();
                        return false;//Les elements presents dans le cout ne correspondent pas avec le fs et aps
                    }
                    return true;
                }
                else
                {
                    auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","Cout vide !",QMessageBox::Ok};
                    info->exec();
                    return false; //Cout vide
                }
            }
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false; //Graphe Vide - Fs & Aps
            }
        }
        else
        {
           if(d_wg.verifieMatrice_NonVide())
           {
               int n = d_wg.getMatrice()[0][0];
               int m = d_wg.getMatrice()[0][1];
               vector<vector<int>> couts = d_wg.getCouts();
               if(couts[0][0] != n || couts[0][1] != m)
               {
                   auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","Les elements presents dans le cout en ligne 0 ne correspondent pas avec la matrice",QMessageBox::Ok};
                   info->exec();
                   return false;//Les elements presents dans le cout ne correspondent pas avec la matrice
               }
               return true;
           }
           else
           {
               auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","Matrice vide !",QMessageBox::Ok};
               info->exec();
               return false; //Graphe Vide - Matrice
           }
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR DANTZIG: ","Graphe non oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
    return false;
}

bool MainWindow::verifieKruskal()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit non oriente.
    if(!d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
            {
                return true;
            }
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR KRUSKAL: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        else if(d_wg.verifieMatrice_NonVide())
        {
            return true;
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR KRUSKAL: ","Matrice vide !",QMessageBox::Ok};
            info->exec();
            return false;
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR KRUSKAL: ","Graphe oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}

bool MainWindow::verifiePruferEncode()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit non oriente.
    if(!d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
                return true;
            else
            {
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR PRUFER_ENCODE: ","FS et APS vide !",QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        else if(d_wg.verifieMatrice_NonVide())
        {
            return true;
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"ERREUR PRUFER_ENCODE: ","Matrice vide !",QMessageBox::Ok};
            info->exec();
            return false;
        }
    }
    else
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR PRUFER_ENCODE: ","Graphe oriente !",QMessageBox::Ok};
        info->exec();
        return false;
    }
}

bool MainWindow::verifiePruferDecode(const vector<int>& p)
{
    unsigned m = p[0];
    if(m != p.size()-1)
    {
        auto info = new QMessageBox{QMessageBox::Warning,"ERREUR PRUFER_DECODE: ","P n'est pas correctement saisi : p[0] contient le nombre total d'elements du tableau",QMessageBox::Ok};
        info->exec();
        return false;
    }
    else
    {
        int nb_max_sommets = m+2;
        for(unsigned i = 1 ; i <= m ; ++i)
        {
            if(p[i] <= 0 || p[i] > nb_max_sommets)
            {
                QString s = "P n'est pas correctement saisi : p[";
                s += s.fromStdString(std::to_string(i));
                s += "] est soit negatif soit superieur a ";
                s += s.fromStdString(std::to_string(p[0]+2));
                auto info = new QMessageBox{QMessageBox::Warning,"ERREUR PRUFER_DECODE: ",s,QMessageBox::Ok};
                info->exec();
                return false;
            }
        }
        return true;
    }
}

void MainWindow::charge()
{
    QString filters =   "Fichiers de Graph (*.graph);;"
                        "Tous les fichiers (*)";

    QString fileName = QFileDialog::getOpenFileName(this, windowTitle(), QDir::currentPath(), filters);

    if(fileName.isEmpty())
    {
        //Afficher message d'erreur
    }
    else if(!fileName.endsWith(".graph"))
    {
        //Afficher message d'erreur
    }
    else
    {
        std::ifstream ifs(fileName.toStdString());

        if(!ifs)
        {
            //Afficher message d'erreur
        }
        else
        {
            d_wg.loadFrom(ifs);
        }
    }
}

void MainWindow::saisieMatrice()
{
    menuMatrice->show();
}

void MainWindow::saisieFSAPS()
{
    menuFSAPS->show();
}

void MainWindow::ajoute()
{
    //Ajoute un noeud
    menuS->show();
}


void MainWindow::supprime()
{
    //Supprime un noeud
    menuSuppr->show();
}

void MainWindow::onClick_Distance()
{
    vector<vector<int>> mat_dist;
    if(verifieDistance())
    {
         mat_dist = d_wg.englobe_Distance();
         QString s = "Résultat de l'algorithme Distance \n";
         for(unsigned i = 0 ; i < mat_dist.size() ; ++i)
         {

             s += s.fromStdString(toStringVector(mat_dist[i])) + "\n";
         }
         // Créer un QLabel pour afficher le message
         QLabel *label = new QLabel(s);
         label->setWordWrap(true); // Activer le retour à la ligne automatique si nécessaire



         // Ajouter le label au layout du cadre de message
         QFrame* m = d_vue.getMessageFrame();

         QLayout* layout = m->layout();
         QLayoutItem* item;
         while ((item = layout->takeAt(0)) != nullptr) {
             delete item->widget(); // Supprimer le widget
             delete item; // Supprimer l'élément du layout
         }

        m->layout()->addWidget(label);
    }
}



void MainWindow::onClick_Rang()
{
    vector<int> rang;
    if(verifieRang())
    {
        rang = d_wg.englobe_Rang();
        QString s = "";
        s += s.fromStdString(toStringVector(rang));
        // Créer un QLabel pour afficher le message
        QLabel *label = new QLabel(s);
        label->setWordWrap(true); // Activer le retour à la ligne automatique si nécessaire



        // Ajouter le label au layout du cadre de message
        QFrame* m = d_vue.getMessageFrame();

        QLayout* layout = m->layout();
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget(); // Supprimer le widget
            delete item; // Supprimer l'élément du layout
        }

        m->layout()->addWidget(label);
    }
}

void MainWindow::onClick_Tarjan()
{
    if(verifieTarjan())
    {
        vector<int> cfc, prem, pred, pilch, baseR, baseI;

        d_wg.englobe_Tarjan(cfc,pilch,pred,prem,baseR,baseI);
        QString s = "";
        s += "cfc : ";
        s += s.fromStdString(toStringVector(cfc));
        s += "\n";
        s += "prem : ";
        s += s.fromStdString(toStringVector(prem));
        s += "\n";
        s += "pilch : ";
        s += s.fromStdString(toStringVector(pilch));
        s += "\n";
        s += "pred : ";
        s += s.fromStdString(toStringVector(pred));
        s += "\n";
        s += "base reduite du graphe reduit : ";
        s += s.fromStdString(toStringVector(baseR));
        s += "\n";
        s += "base initiale du graphe : ";
        s += s.fromStdString(toStringVector(baseI));
        s += "\n";
        // Créer un QLabel pour afficher le message
        QLabel *label = new QLabel(s);
        label->setWordWrap(true); // Activer le retour à la ligne automatique si nécessaire



        // Ajouter le label au layout du cadre de message
        QFrame* m = d_vue.getMessageFrame();

        QLayout* layout = m->layout();
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget(); // Supprimer le widget
            delete item; // Supprimer l'élément du layout
        }

        m->layout()->addWidget(label);
    }
}

void MainWindow::onClick_Ordonnancement()
{
    menuOrd->show();
}

void MainWindow::onClick_Dijkstra()
{
    menuDijkstra->show();
}

void MainWindow::onClick_Dantzig()
{
    if(verifieDantzig())
    {
        if(d_wg.englobe_Dantzig())
        {
            QString s = "";
            s += "cout : ";
            for(unsigned i = 0 ; i < d_wg.getCouts().size() ; ++i)
            {
                s += s.fromStdString(toStringVector(d_wg.getCouts()[i]));
                s += "\n";
            }
            // Créer un QLabel pour afficher le message
            QLabel *label = new QLabel(s);
            label->setWordWrap(true); // Activer le retour à la ligne automatique si nécessaire



            // Ajouter le label au layout du cadre de message
            QFrame* m = d_vue.getMessageFrame();

            QLayout* layout = m->layout();
            QLayoutItem* item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget(); // Supprimer le widget
                delete item; // Supprimer l'élément du layout
            }

            m->layout()->addWidget(label);
        }
        else
        {
            auto info = new QMessageBox{QMessageBox::Warning,"Erreur Dantzig :","Presence d'un circuit absorbant : ",QMessageBox::Ok};
            // Créer un QLabel pour afficher le message
            QLabel *label = new QLabel(info);
            label->setWordWrap(true); // Activer le retour à la ligne automatique si nécessaire



            // Ajouter le label au layout du cadre de message
            QFrame* m = d_vue.getMessageFrame();

            QLayout* layout = m->layout();
            QLayoutItem* item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget(); // Supprimer le widget
                delete item; // Supprimer l'élément du layout
            }

            m->layout()->addWidget(label);
        }
    }
}

void MainWindow::onClick_Kruskal()
{
    if(verifieKruskal())
    {
        d_wg.englobe_Kruskal();
    }
}

void MainWindow::onClick_Prufer_encode()
{
    if(verifiePruferEncode())
    {
        vector<int> p = d_wg.englobe_Prufer_encode();
        QString s;
        auto info = new QMessageBox{QMessageBox::Information,"Resultat du codage de Prufer : ",s.fromStdString(toStringVector(p)),QMessageBox::Ok};
        // Créer un QLabel pour afficher le message
        QLabel *label = new QLabel(info);
        label->setWordWrap(true); // Activer le retour à la ligne automatique si nécessaire



        // Ajouter le label au layout du cadre de message
        QFrame* m = d_vue.getMessageFrame();

        QLayout* layout = m->layout();
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget(); // Supprimer le widget
            delete item; // Supprimer l'élément du layout
        }

        m->layout()->addWidget(label);
    }
}

void MainWindow::onClick_Prufer_decode()
{
    menuPruferD->show();
}

void MainWindow::onValiderAjout()
{
    vector<int> Pred;
    vector<int> Suc;

    vector<int> menuPred = menuS->getPred();
    vector<int> menuSuc = menuS->getSuc();

    int k1 = 1;
    int k2 = 1;


    int nbNoeud = d_wg.getAps()[0] + 2;

    for(int i = 0; i < nbNoeud; i++)
    {
        if(menuPred[k1] == i)
        {
            Pred.push_back(1);
            k1++;
        }
        else
            Pred.push_back(0);
        if(menuSuc[k2] == i)
        {
             Suc.push_back(1);
             k2++;
        }
        else
            Suc.push_back(0);
    }

    Noeud n{d_wg.getAps()[0] + 1};
    d_wg.ajouterNoeud(n, Pred, Suc);
}

void MainWindow::onValiderPruferDecode()
{
    if(verifiePruferDecode(menuPruferD->getP()))
    {
        d_wg.englobe_Prufer_decode(menuPruferD->getP());
    }
}

void MainWindow::onValiderDijkstra()
{
    vector<int> d, pr;
    if(verifieDijkstra(menuDijkstra->getSommet()))
    {
        d_wg.englobe_Dijkstra(menuDijkstra->getSommet(),d,pr);
        QString s = "";
        s += "distance : ";
        s += s.fromStdString(toStringVector(d));
        s += "\n";
        s += "pr : ";
        s += s.fromStdString(toStringVector(pr));
        auto info = new QMessageBox{QMessageBox::Information,"Resultat de Dijkstra",s,QMessageBox::Ok};
        info->exec();
    }
}

void MainWindow::onValiderOrdonnancement()
{
    if(verifieOrdonnancement())
    {
        vector<int> long_critique;
        d_wg.englobe_Ordonnancement(menuOrd->getDuree(),menuOrd->getFp(),menuOrd->getApp(),long_critique);
        QString s = "";
        auto info = new QMessageBox{QMessageBox::Information,"Resultat de l'ordonnancement : Longueur Critique",s.fromStdString(toStringVector(long_critique)),QMessageBox::Ok};
        info->exec();
    }
}

void MainWindow::onValideSaisieFSAPS()
{
    //A faire quand on pourra charger des graphes
    vector<int> FS = menuFSAPS->getFS();
    vector<int> APS = menuFSAPS->getAPS();
    Graph g{FS, APS, menuFSAPS->getCheckOriente()};
    if(menuFSAPS->getCheck())
    {
        vector<vector<int>> cout = menuFSAPS->getCout();
        g.setCout(cout);
    }
    cout<<g.getEst_oriente();
    d_wg.loadGraph(g);
}

void MainWindow::onValideSaisieMatrice()
{
    vector<vector<int>> matrice = menuMatrice->getMatrice();
    Graph g{matrice, menuMatrice->getCheckOriente()};
    if(menuMatrice->getCheck())
    {
        vector<vector<int>> cout = menuMatrice->getCout();
        g.setCout(cout);
    }
    cout<<g.getEst_oriente();
    d_wg.loadGraph(g);
}

