#include "FichierUtilisateur.h"

int estPresent(const char* nom)
{
  int fd = open(FICHIER_UTILISATEURS, O_RDONLY);

  if (fd == -1)
  {
    return -1;
  }
  else
  {
    UTILISATEUR u;
    int i = 0, rc;

    while((rc = read(fd, &u, sizeof(UTILISATEUR))) >0 )
    {
      if (strcmp(u.nom, nom) == 0)
      {
        close(fd);
        return i + 1;
      }
      i++;
    }

    close(fd);
    return 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////
int hash(const char* motDePasse)
{
  int mdpHashe, i = 1, x = 0;
  char buffer[2];

  while(*motDePasse != '\0')
  {

    x += (*motDePasse) * i;

    motDePasse++;
    i++;
  }

  printf("modulo de %d par 97 est %d", x, mdpHashe);
  mdpHashe = x % 97;

  return mdpHashe;
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char* nom, const char* motDePasse)
{
  int fd = open(FICHIER_UTILISATEURS, O_WRONLY | O_APPEND | O_CREAT, 0644);
  int w;
  UTILISATEUR u;

  if(fd == -1)
  {
    perror("Erreur de open dans la fonction ajouteUtilisateur");
  }
  else
  {
    strcpy(u.nom, nom);
    u.hash = hash(motDePasse);

    w = write(fd, &u, sizeof(UTILISATEUR));
    if(w == -1)
    {
      perror("Erreur de write dans la fonction ajouteUtilisateur");
    }
  }
  
  close(fd);
}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char* motDePasse)
{
  UTILISATEUR u;
  int fd = open(FICHIER_UTILISATEURS, O_RDWR );
  int l, r;

  if(fd == -1)
  {
    return -1;
  }
  else{
    l = lseek(fd, sizeof(UTILISATEUR)* (long)(pos - 1), SEEK_SET);
    
    if(l  == -1)
    {
      perror("Erreur de lseek dans la fonction verifieMotDePasse");
      close(fd);
      return -1;
    }
    else{
      r = read(fd, &u, sizeof(UTILISATEUR));

      if(r < 0)
      {
        perror("Erreur de read dans la fonction verifieMotDePasse");
        close(fd);
        return -1;
      }
      else{
        if(u.hash == (hash(motDePasse)))
        {
          close(fd);
          return 1;
        }
      }
    }
  }

  close(fd);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  int fd = open(FICHIER_UTILISATEURS, O_RDONLY); 
  int i = 0;
  UTILISATEUR u;

  if(fd == -1)
  {
    perror("Erreur de open dans la fonction listeUtilisateurs");
    return -1;
  }
  else{
    while(read(fd, &u, sizeof(UTILISATEUR)) > 0)
    {
      vecteur[i] = u;
      i++;
    }

    close(fd);
    return i;
  }
  
  return 0;
}
