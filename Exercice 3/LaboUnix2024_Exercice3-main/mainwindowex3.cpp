#include "mainwindowex3.h"
#include "ui_mainwindowex3.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

MainWindowEx3::MainWindowEx3(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx3)
{
    ui->setupUi(this);
}

MainWindowEx3::~MainWindowEx3()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::setGroupe1(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx3::setGroupe2(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx3::setGroupe3(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx3::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx3::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx3::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx3::recherche1Selectionnee()
{
  return ui->checkBoxRecherche1->isChecked();
}

bool MainWindowEx3::recherche2Selectionnee()
{
  return ui->checkBoxRecherche2->isChecked();
}

bool MainWindowEx3::recherche3Selectionnee()
{
  return ui->checkBoxRecherche3->isChecked();
}

const char* MainWindowEx3::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe3()
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
void MainWindowEx3::on_pushButtonLancerRecherche_clicked()
{
  int status, res, idFils1, idFils2, idFils3, idF, fd, fdDup, fdDupF1, fdDupF2, fdDupF3;

  if ((fd = open("Trace.log",O_RDWR | O_CREAT,0744)) == -1)
  {
    perror("Erreur de open()");
    exit(1);
  }

  if ((fdDup = dup2(fd, 2)) == -1)
  {
    perror("Erreur de dup2()");
    exit(1);
  }
  
  fprintf(stderr,"Clic sur le bouton Lancer Recherche\n");

  if ((recherche1Selectionnee()) && (getGroupe1() != NULL))
  {
    if((idFils1 = fork()) == -1)
    {
      perror("Erreur de Fork() fils 1");
    }
  }

  if ((recherche2Selectionnee()) && (getGroupe2() != NULL))
  {
    if((idFils2 = fork()) == -1)
    {
      perror("Erreur de Fork() fils 2");
    }
  }

  if ((recherche3Selectionnee()) && (getGroupe3() != NULL))
  {
    if((idFils3 = fork()) == -1)
    {
      perror("Erreur de Fork() fils 3");
    }
  }

  if (idFils1 == 0)
  {
    if ((fdDupF1 = dup2(fdDup,2)) == -1)
    {
      perror("Erreur de dup2()");
      exit(1);
    }

    if(execl("./Lecture", "Lecture", MainWindowEx3::getGroupe1(), NULL) == -1)
    {
      perror("Erreur de EXECL fils 1\n");
      exit(1);
    }
  }

  if (idFils2 == 0)
  {
    if ((fdDupF2 = dup2(fdDup,2)) == -1)
    {
      perror("Erreur de dup2()");
      exit(1);
    }

    if(execl("./Lecture", "Lecture", MainWindowEx3::getGroupe2(), NULL) == -1)
    {
      perror("Erreur de EXECL fils 2\n");
      exit(1);
    }
  }

  if (idFils3 == 0)
  {
    if ((fdDupF3 = dup2(fdDup,2)) == -1)
    {
      perror("Erreur de dup2()");
      exit(1);
    }

    if(execl("./Lecture", "Lecture", MainWindowEx3::getGroupe3(), NULL) == -1)
    {
      perror("Erreur de EXECL fils 3\n");
      exit(1);
    }
  }
  
  while((idF = wait(&status)) != -1)
  {
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
      MainWindowEx3::setResultat1(res);
    }

    if(idF == idFils2)
    {
      res = WEXITSTATUS(status);
      MainWindowEx3::setResultat2(res);
    }

    if(idF == idFils3)
    {
      res = WEXITSTATUS(status);
      MainWindowEx3::setResultat3(res);
    }
  }
}

void MainWindowEx3::on_pushButtonVider_clicked()
{
  //Suppression des valeur dans les champs groups
  ui->lineEditGroupe1->clear();
  ui->lineEditGroupe2->clear();
  ui->lineEditGroupe3->clear();

  //Suppression des valeur dans les champs resultats
  ui->lineEditResultat1->clear();
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();
}

void MainWindowEx3::on_pushButtonQuitter_clicked()
{
  on_pushButtonVider_clicked();
  delete ui;
  exit(0);
}
