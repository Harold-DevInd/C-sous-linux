#include "mainwindowex4.h"
#include "ui_mainwindowex4.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

extern MainWindowEx4 *w;

int idFils1, idFils2, idFils3;
void HandlerSIGCHLD(int);
struct sigaction A;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindowEx4::MainWindowEx4(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx4)
{
  ui->setupUi(this);
  ui->pushButtonAnnulerTous->setVisible(false);

  // armement de SIGCHLD
  A.sa_handler = HandlerSIGCHLD;
  sigemptyset(&A.sa_mask);
  A.sa_flags = 0;

  if (sigaction(SIGCHLD, &A, NULL))
  {
    perror("Erreur de sigaction");
    exit(1);
  }
}

MainWindowEx4::~MainWindowEx4()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx4::setGroupe1(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx4::setGroupe2(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx4::setGroupe3(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx4::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx4::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx4::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx4::traitement1Selectionne()
{
  return ui->checkBoxTraitement1->isChecked();
}

bool MainWindowEx4::traitement2Selectionne()
{
  return ui->checkBoxTraitement2->isChecked();
}

bool MainWindowEx4::traitement3Selectionne()
{
  return ui->checkBoxTraitement3->isChecked();
}

const char* MainWindowEx4::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx4::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx4::getGroupe3()
{
  if (ui->lineEditGroupe3->text().size())
  { 
    strcpy(groupe3,ui->lineEditGroupe3->text().toStdString().c_str());
    return groupe3;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx4::on_pushButtonDemarrerTraitements_clicked()
{
  int fd;
  
  fprintf(stderr,"Clic sur le bouton Lancer Recherche\n");

  if ((traitement1Selectionne()) && (getGroupe1() != NULL))
  {
    if((idFils1 = fork()) == -1)
    {
      perror("Erreur de Fork() fils 1");
      exit(1);
    }
    else if (idFils1 == 0)
          {
            if(execl("./Traitement", "Traitement", getGroupe1(), "200", NULL) == -1)
            {
              perror("Erreur de EXECL fils 1\n");
              exit(1);
            }
          }
  }

  if ((traitement2Selectionne()) && (getGroupe2() != NULL))
  {
    if((idFils2 = fork()) == -1)
    {
      perror("Erreur de Fork() fils 2");
      exit(1);
    }
    else if (idFils2 == 0)
          {
            if(execl("./Traitement", "Traitement", getGroupe2(), "450", NULL) == -1)
            {
              perror("Erreur de EXECL fils 2\n");
              exit(1);
            }
          }
  }

  if ((traitement3Selectionne()) && (getGroupe3() != NULL))
  {
    if((idFils3 = fork()) == -1)
    {
      perror("Erreur de Fork() fils 3");
      exit(1);
    } 
    else if (idFils3 == 0)
    {
      if(execl("./Traitement", "Traitement", getGroupe3(), "700", NULL) == -1)
      {
        perror("Erreur de EXECL fils 3\n");
        exit(1);
      }
    }
  }  
}

void MainWindowEx4::on_pushButtonVider_clicked()
{
  fprintf(stderr,"Clic sur le bouton Vider\n");
  //Suppression des valeur dans les champs groups
  ui->lineEditGroupe1->clear();
  ui->lineEditGroupe2->clear();
  ui->lineEditGroupe3->clear();

  //Suppression des valeur dans les champs resultats
  ui->lineEditResultat1->clear();
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();
}

void MainWindowEx4::on_pushButtonQuitter_clicked()
{
  on_pushButtonVider_clicked();
  delete ui;
  exit(0);
}

void MainWindowEx4::on_pushButtonAnnuler1_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler1\n");
  if((kill(idFils1, SIGUSR1)) == -1)
  {
    perror("Erreur lors du kill");
    exit(1);
  } 
}

void MainWindowEx4::on_pushButtonAnnuler2_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler2\n");
  if((kill(idFils2, SIGUSR1)) == -1)
  {
    perror("Erreur lors du kill");
    exit(1);
  } 
}

void MainWindowEx4::on_pushButtonAnnuler3_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler3\n");
  if((kill(idFils3, SIGUSR1)) == -1)
  {
    perror("Erreur lors du kill");
    exit(1);
  } 
}

void MainWindowEx4::on_pushButtonAnnulerTous_clicked()
{
  // fprintf(stderr,"Clic sur le bouton Annuler tout\n");
  // NOTHING TO DO --> bouton supprimé
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Handlers de signaux //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HandlerSIGCHLD(int sig)
{
  int status, res, idF;

  if((idF = wait(&status)) == -1)
  {
    perror("Erreur dans le wait");
    exit(0);
  }
    
  if ((idF != idFils1) && (idF != idFils2) && (idF != idFils3))
  {
    perror("Pas le bon fils \n");
    exit(3);
  }

  if(!WIFEXITED(status))
  {
    perror("Fils non terminé par exit \n");
  }

  if(idF == idFils1)
  {
    res = WEXITSTATUS(status);
    w->setResultat1(res);
  }
  else if(idF == idFils2)
        {
          res = WEXITSTATUS(status);
          w->setResultat2(res);
        }
        else if(idF == idFils3)
              {
                res = WEXITSTATUS(status);
                w->setResultat3(res);
              }
}