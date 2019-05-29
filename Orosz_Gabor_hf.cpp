#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define MAX2 80

//Strukt�r�k
struct tombok
{
int azonosito;
char cim[MAX2];
float ertek;
};

struct indextabla
{
int azon;
int poz;
struct indextabla *kovetkezo;
};

//Funkci�k
int tombfeltoltes(),kereses(),modositas(),torles(),listazas(),kilep(),indexeles();

//V�ltoz�k �s t�mb�k
int db=0,keresendo=0,torolt=0;
bool talalt=false;
int beSzam;
char beCim[MAX2];
float beErtek;
FILE *fp;
struct indextabla *uj, *elso = NULL, *aktualis, *elozo = NULL;
int byte=sizeof(beSzam)+sizeof(beCim)+sizeof(beErtek);

//A main funkci� tartalmazza a men�t �s lefuttatja a k�rt funkci�t. Hiba eset�n hiba�zenetet �r ki.
int main()
{	
	int valasztas;
	bool kilepes=false;
	
	//C�m
	printf(" Orosz Gabor\n Hazi feladat\n Film adatbazis\n\n A program filmek azonositojat, cimet es ertekeleset tartalmazo,\n adatbazis letrehozasara es modositasara alkalmas.\n Ezen kivul meg lehetoseg van rekordok keresesere, torlesere es listazasara is.\n");
	printf("\n Figyelem!\n Adatmegadasnal szokoz helyett alulvonast(_) kell hasznalni,\n kulonben nem fog helyesen mukodni a program!\n Az ertekeles kivetelevel mindenhol egesz szamot kell hasznalni!");
	
	//Adatb�zis beolvas�sa
	fp=fopen("adatbazis.bin","r+b");
	
	if(fp==NULL)
	{
		fclose(fp);
		
		printf("\n\n Hibas fajl megnyitas!");
		fp=fopen("adatbazis.bin","w+b");
		fclose(fp);
		printf("\n Uj adatbazis fajl letrehozva!");
	}
	else
	{
		fp=fopen("adatbazis.bin","r+b");
	
		fseek(fp,byte*db,SEEK_SET);
		fread(&beSzam, sizeof(beSzam), 1, fp);
		db++;
		
		while(!feof(fp))
		{
			indexeles();
	
			fseek(fp,byte*db,SEEK_SET);
			fread(&beSzam, sizeof(beSzam), 1, fp);
			db++;
		}
		fclose(fp);
        db--;
	}
	aktualis = elso;
	
	//Men�
	while(kilepes!=true)
	{
		printf("\n\n 1. Adatfeltoltes\n 2. Kereses\n 3. Modositas\n 4. Torles\n 5. Listazas\n 6. Kilepes\n");
		printf("\n Valasztas(1-6): ");
		scanf("%d",&valasztas);
		
		switch(valasztas)
		{
			//Adatfelt�lt�s
			case 1:
			{
				system("cls");
				tombfeltoltes();
				break;

				//Keres�s
				case 2:
				{
					system("cls");
					kereses();
					break;

					//M�dos�t�s
					case 3:
					{
						system("cls");
						modositas();
						break;

						//T�rl�s
						case 4:
						{
							system("cls");
							torles();
							break;

							//List�z�s
							case 5:
							{
								system("cls");
								listazas();
								break;

								//Kil�p�s
								case 6:
								{
									system("cls");
									kilep();
									kilepes=true;
									break;

									//Hiba�zenet
									default:
									system("cls");
									printf(" Nincs ilyen funkcio!\n");
									break;
								}
								system("pause");
							}
						}
					}
				}
			}
		}
	}
}

//A t�mbfelt�lt�s funkci� bek�ri a film adatait �s be�rja azokat a t�mb�kbe. Hiba eset�n hiba�zenetet �r ki.
int tombfeltoltes()
{
	fp=fopen("adatbazis.bin","a+b");
	int bovit=0;
	bool azon_letezik=false;

	//Adatfelt�lt�s
	do
	{
		bovit=0;
		printf("\n	Adatfeltoltes:\n");
		db++;
		
		//�j azonos�t� bek�r�se
		do
		{
			azon_letezik=false;
			printf("\n Kerem a film azonositojat(1-20): ");
			scanf("%d",&beSzam);

			while(beSzam<1 || beSzam>MAX)
			{
				printf(" Hibas szamot adott meg!\n");
				printf("\n Kerem a film azonositojat(1-20): ");
				scanf("%d",&beSzam);
			}
			aktualis=elso;
			
			while(aktualis)
			{
				if(aktualis->azon==beSzam)
				{
						beSzam='\0';
						printf(" Ez az azonosito mar letezik! Probaljon meg egy masikat!\n");
						azon_letezik=true;
						break;
				}
			elozo = aktualis;
			aktualis = aktualis->kovetkezo;
			}
		}
		while(azon_letezik==true);
		
		//�j c�m
		printf(" Kerem a film cimet(Szokoz helyett alulvonast(_) kell irni!): ");
		scanf("%s",&beCim);
		
		//�j �rt�kel�s
		printf(" Kerem a film ertekeleset(1-10): ");
		scanf("%f",&beErtek);

		while(beErtek<1 || beErtek>10)
		{
			printf(" Hibas ertekelest adott!");
			printf("\n Kerem a film ertekeleset(1-10): ");
			scanf("%f",&beErtek);
		}
		
		//Rekord f�jlba ment�se
		fwrite(&beSzam, sizeof(beSzam), 1, fp);
		fwrite(&beCim, sizeof(beCim), 1, fp);
		fwrite(&beErtek, sizeof(beErtek), 1, fp);
		
		//�j index ment�se
		indexeles();
		
		printf("\n Szeretne meg adatot felvenni 1(igen) vagy 0(nem)? ");
		scanf("%d",&bovit);
		
		if(bovit!=1 && bovit!=0)
		{
			printf(" Hibas szamot adott meg!\n");
			printf("\n Szeretne meg adatot felvenni 1(igen) vagy 0(nem)? ");
			scanf("%d",&bovit);
		}
		aktualis = elso;
    while (aktualis) 
    {        
        printf("\nAzon: %d\nPoz: %d\n", aktualis->azon,aktualis->poz);
        aktualis=aktualis->kovetkezo;        
    }
	}
	while(bovit==1);
	fclose(fp);
}

//A keres�s funkci� bek�ri a keresend� film azonos�t�j�t �s ki�rja a film adatait. Hiba eset�n hiba�zenetet �r ki.
int kereses()
{
	fp=fopen("adatbazis.bin","r+b");
	
	if (db>0)
	{
		talalt=0;
		printf(" Kerem a film azonositojat(1-20): ");
		scanf("%d",&keresendo);

		while(keresendo<1 || keresendo>MAX)
		{
			printf(" Hibas szamot adott meg!\n");
			printf("\n Kerem a film azonositojat(1-20): ");
			scanf("%d",&keresendo);
		}
		
		aktualis = elso;
		elozo = NULL;
		
		while(aktualis)
		{	
			if(aktualis->azon==keresendo)
			{
				talalt=true;
				
				fseek(fp,byte*aktualis->poz,SEEK_SET);
				fread(&beSzam, sizeof(beSzam), 1, fp);
				fread(&beCim, sizeof(beCim), 1, fp);
				fread(&beErtek, sizeof(beErtek), 1, fp);
					
				printf(" ___________________________________________\n");
				printf(" Azonosito		 Cim	   Ertekeles\n");
				printf(" ___________________________________________\n");
				printf(" %d %24s %15.1f\n",beSzam, beCim, beErtek);
				printf(" ___________________________________________\n");
				
				break;
			}
			aktualis = aktualis->kovetkezo;
		}
		
		if(!talalt)
    	{
        	printf(" Nincs ilyen azonosito!\n");   
    	}
	}
	else
	{
		talalt=false;
		printf("\n Ures az adatbazis!\n");
	}
	fclose(fp);
}

//A m�dos�t�s funkci� el�sz�r lefuttatja a keres�s funkci�t azt�n bek�ri az �j adatokat. Hiba eset�n hiba�zenetet �r ki.
int modositas()
{
	if (db>0)
	{
		kereses();

		if(talalt)
		{
			fp=fopen("adatbazis.bin","r+b");
			
			printf("\n Kerem a film uj cimet(Szokoz helyett alulvonast(_) kell irni!): ");
			scanf("%s",&beCim);
			printf(" Kerem a film uj ertekeleset(1-10): ");
			scanf("%f",&beErtek);

			while(beErtek<=0 || beErtek>10)
			{
				printf(" Hibas ertekelest adott!\n");
				scanf("%f",&beErtek);
			}	
			fseek(fp, byte*aktualis->poz, SEEK_SET);
			fwrite(&beSzam, sizeof(beSzam), 1, fp);
			fwrite(&beCim, sizeof(beCim), 1, fp);
			fwrite(&beErtek, sizeof(beErtek), 1, fp);
			
			printf(" ___________________________________________\n");
			printf(" Azonosito		 Cim	   Ertekeles\n");
			printf(" ___________________________________________\n");
			printf(" %d %24s %15.1f\n", beSzam, beCim, beErtek);
			printf(" ___________________________________________\n");
			printf("\n A rekord modositva lett!\n");
		}
	}
	else
	{
		printf("\n Ures az adatbazis!\n");
	}
	fclose(fp);
}

//A t�rl�s funkci� el�sz�r lefuttatja a keres�s funkci�t majd r�k�rdez hogy biztosan akarjuk e t�r�lni az adatot. Hiba eset�n hiba�zenetet �r ki.
int torles()
{
	int biztos=0;

	if (db>0)
	{
		kereses();

		if(talalt==1)
		{
			printf("\n Biztosan torolni akarja a rekordot 1(igen) vagy 0(nem)? ");
			scanf("%d",&biztos);

			if(biztos==1)
			{
				aktualis = elso; 
    			elozo = NULL;
    
    			while(aktualis)
    			{
        			if(keresendo == aktualis->azon)
        			{
            			if(!elozo)
            			{
                			elso = aktualis->kovetkezo;   
            			}
            			else
            			{
                			elozo->kovetkezo = aktualis->kovetkezo;
            			}
            			free(aktualis);
            			break;
        			}
        			elozo = aktualis;
        			aktualis = aktualis->kovetkezo;        
    			}
    			torolt=1;
				printf("\n Rekord torolve!\n");
				listazas();
			}
			else if(biztos==0)
			{
				printf("\n Az adatbazis valtozatlan maradt.\n");
			}
			else
			{
				printf(" Rossz szamot adott meg!\n");
				printf("\n Biztosan torolni akarja a rekordot 1(igen) vagy 0(nem)? ");
				scanf("%d",&biztos);
			}
		}
	}
	else
	{
		printf("\n Ures az adatbazis!\n");
	}
}

//A list�z�s funkci� el�sz�r elrendezi a t�mb�ket azonos�t�k alapj�n majd ki�rja az adatokat egy form�zott t�bl�zatban. Hiba eset�n hiba�zenetet �r ki.
int listazas()
{
	fp=fopen("adatbazis.bin","r+b");
	
	if(db>0)
	{
		//Kiir�s
		printf(" ___________________________________________\n");
		printf(" 		  Adatbazis\n");
		printf(" ___________________________________________\n");
		printf(" Azonosito		 Cim	   Ertekeles\n");
		printf(" ___________________________________________\n");
		
		aktualis = elso;

		while(aktualis)
		{
                fseek(fp, byte*aktualis->poz, SEEK_SET);
				fread(&beSzam, sizeof(beSzam), 1, fp);
				fread(&beCim, sizeof(beCim), 1, fp);
				fread(&beErtek, sizeof(beErtek), 1, fp);
					
				printf(" %d %24s %15.1f\n",beSzam,beCim,beErtek);
				printf(" ___________________________________________\n");
				
				aktualis = aktualis->kovetkezo;
  		}
	}
	else
	{
		printf("\n Ures az adatbazis!\n");
    }
    fclose(fp);
}

//Kil�p�s funkci�. V�grehajtja a fizikai t�rl�st ha sz�ks�ges.
int kilep()
{
	if(torolt==1)
	{
		tombok tempTomb[MAX];
		int k=0;
		fp=fopen("adatbazis.bin","r+b");
	
		if(db>0)
		{
			int poztemp=0;
		
			while(!feof(fp))
			{
				fseek(fp, byte*poztemp, SEEK_SET);
				fread(&beSzam, sizeof(beSzam), 1, fp);
			
				aktualis = elso;
				elozo = NULL;
			
				while(aktualis)
				{
				//Rekord temp t�mbbe ment�se
				if(aktualis->azon==beSzam)
				{	
					fread(&tempTomb[k].cim, sizeof(tempTomb[k].cim), 1, fp);
					fread(&tempTomb[k].ertek, sizeof(tempTomb[k].ertek), 1, fp);
					tempTomb[k].azonosito=beSzam;
					k++;
					break;
				}
				aktualis = aktualis->kovetkezo;
				}
				poztemp++;
    		}
		}
		fclose(fp);
		
		//Eredeti adatb�zis fel�l�r�sa �j adatokkal
		fp=fopen("adatbazis.bin","w+b");
		fseek(fp, 0, SEEK_SET);
		
		for(k=0;k<db-1;k++)
		{
			fwrite(&tempTomb[k].azonosito, sizeof(tempTomb[k].azonosito), 1, fp);
			fwrite(&tempTomb[k].cim, sizeof(tempTomb[k].cim), 1, fp);
			fwrite(&tempTomb[k].ertek, sizeof(tempTomb[k].ertek), 1, fp);
		}
		fclose(fp);
	}
}

//�j index
int indexeles()
{
	uj = (struct indextabla*)malloc(sizeof(struct indextabla));
        
        if (!uj) 
        {
            printf("Nincs eleg memoria!");
            system("pause");
            
            return -1;
        }
        elozo = NULL;
        aktualis = elso;
    
        while (aktualis && beSzam > aktualis->azon) 
        {        
            elozo = aktualis;
            aktualis = aktualis->kovetkezo; 
        }
        
        if (!elozo) 
        {            
            elso = uj;            
        }
        
        else 
        {            
            elozo->kovetkezo = uj;            
        }
        uj->azon = beSzam;
        uj->poz = db-1;
        uj->kovetkezo = aktualis;    
}
