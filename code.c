#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<math.h>
#include<conio.h>
#include<stdio.h>
#define size1 600
#define size2 300
int costInt[20],t,countForTotalNodesUsed = 0,countForTotalNodes = 0,makeEdge = 0,cost[100][100];
int j,texta = 0,flag3,flag2 = 0,flag4 = 0,countTotalEdges =  0;
float arr[100][2],temp[1][2],usedNode[300][4],checkNotSame[1][2],xCoo,yCoo,avgx,avgy;
char character2,character1,printvalue[] = "Cost: ",costCharacterRem[100][20],edge[100][100];
int valueInputFlag,texta2,sum,costCharacterNumber = -1,node1OfEdge,node2OfEdge,index,solutionDone = 0;
char costCharacters[20]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
 void   draw()
        {
        float buttonVertexX1,buttonVertexX2,buttonVertexY1,buttonVertexY2;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        j = 0;
        while(j!=countTotalEdges)
        {
    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_LINES);
    glVertex3d(usedNode[j][0],usedNode[j][1],1.0f);
    glVertex3d(usedNode[j][2],usedNode[j][3],1.0f);
    glEnd();
      t = 0;


      avgx = (usedNode[j][0]+usedNode[j][2])/2;
          avgy = (usedNode[j][1]+usedNode[j][3])/2;
          float tan  = (usedNode[j][1] - usedNode[j][3])/(usedNode[j][0]- usedNode[j][2]);
          if( tan < 0 )
          glRasterPos3d(avgx+.02,avgy+.02,0.0f);
          else
           glRasterPos3d(avgx-.05,avgy+.02,0.0f);
          if ( costCharacterRem[j][0] != '0' && costCharacterRem[j][0] !='\0' )
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,costCharacterRem[j][t]);
            t++;
        }
      while(costCharacterRem[j][t]!= '\0' )
      {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,costCharacterRem[j][t]);
            t++;
        }
        j++;
        }
        int i = 0 ;
        character1 = '0';
        character2 = '0';
        while( i!=countForTotalNodes)
        {
            // flag 4 remembers the firstNode and makes it yellow
            // flag 3 checks whether the right clicked member is a node or not!
            flag4 = 0;
            j = 0;
            flag3 = 0;
            while( j != countForTotalNodesUsed)
            {
                if( ( arr[i][0]== usedNode[j][0] && arr[i][1]==usedNode[j][1] )|| ( arr[i][0]== usedNode[j][2] && arr[i][1]==usedNode[j][3] ))
                {
                    flag3 = 1;
                    if ( arr[i][0]== usedNode[countTotalEdges][0] && arr[i][1]== usedNode[countTotalEdges][1] )
                        flag4 = 1;
                    break;
                }
                j++;
            }
            if( flag3 == 1 && flag4 == 1)
            glColor3f(1.0f,1.0f,0.0f);
            else if ( flag3 == 1 && flag4 == 0)
                glColor3f(0.0f,1.0f,0.0f);
            else
                glColor3f(1.0f,0.0f,0.0f);
             glPushMatrix();
        glTranslatef(arr[i][0],arr[i][1],0.0f);
            glutSolidSphere(.025f,20,20);
            glPopMatrix();

            //sprintf(number,"%d",10);
                //if( character)
                glPushMatrix();
                glColor3f(1.0,1.0,0.0);
                glRasterPos3d(arr[i][0]+.02,arr[i][1]+0.018f,0.0f);
            if ( character1 != '0' )
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,character1);
        }
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,character2);
            i++;
            character2++;
            if( i%10 == 0 && i!=0)
            {
                character1++;
                character2 = '0';
            }
            glPopMatrix();

        }


    if ( valueInputFlag == 1)
            {
            glRasterPos3d(.5,0.9,0);
            while( printvalue[texta]!='\0')
            {
                glPushMatrix();
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,printvalue[texta]);
            texta++;
            glPopMatrix();
            }
            texta2 = 0;
            while(costCharacters[texta2] != '\0' )
            {
                glPushMatrix();
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,costCharacters[texta2]);
            texta2++;
            texta++;
            glPopMatrix();

            }
            texta = 0;
            }


         buttonVertexX1 = (float)500/size2-1;
         buttonVertexY1 = 1- (float)500/size2;
         buttonVertexX2 = (float)580/size2-1;
         buttonVertexY2 = 1- (float)550/size2;
         glColor3f(1.0f,0.0f,0.0f);
         if (solutionDone == 1)
         glColor3f(1.0f,0.0f,1.0f);
            glPushMatrix();
            glBegin(GL_QUADS);
            glTranslatef(0.0,0.0,0.0);
            glVertex3f( buttonVertexX1,buttonVertexY1,0.0f);
            glVertex3f( buttonVertexX2,buttonVertexY1,0.0f);
            glVertex3f( buttonVertexX2,buttonVertexY2,0.0f);
            glVertex3f( buttonVertexX1,buttonVertexY2,0.0f);
            glEnd();
            glPopMatrix();


                    glutSwapBuffers();
}


void renderScene(int button,int state,int x,int y)
{
    int i,go ;
    if(solutionDone == 0)
    {
    if( x>500 && x<580 && y>500 && y<550 && state == GLUT_DOWN)
    {
        draw();
         for( int q = 0 ; q<countForTotalNodes;q++)
         {
        for( int l = 0 ; l<countForTotalNodes;l++)
            {
            printf("%d\t",edge[q][l]);

             }
        printf("\n");
    }
        solutionDone = 1;
    }
 else
 {
  if ( valueInputFlag == 0)
  {
         xCoo = (float)x/size2-1;
         yCoo = 1-(float)y/size2;

    if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
    {
          i = 0;
         go = 0;
    while( i != countForTotalNodes)
    {
        if (xCoo < (arr[i][0] + 0.05) && xCoo>(arr[i][0]-0.05)&&yCoo > arr[i][1]-0.05 && yCoo<(arr[i][1]+0.05)  )
        {
            go = 1;
            break;
        }
        i++;
    }
    if (go==0)
    {
        arr[countForTotalNodes][0] = xCoo;
        arr[countForTotalNodes][1] = yCoo;
        countForTotalNodes++;

    }
    draw();
    }




    //flag2 checks is it first node of the edge or second node of the edge
    //ValueInputFlag
    else if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
            temp[0][0] = (float)x/size2-1;
            temp[0][1] = 1-(float)y/size2;
            for ( i = 0; i < countForTotalNodes; i++ )
            {
                if ( temp[0][0] < (arr[i][0] + 0.025) && temp[0][0]>(arr[i][0]-0.025)&&temp[0][1] > arr[i][1]-0.025 && temp[0][1]<(arr[i][1]+0.025)  )
                {
                    if( checkNotSame[0][0]!=arr[i][0] || checkNotSame[0][1]!=arr[i][1] || flag2 == 0)
                    {
                    checkNotSame[0][0] = arr[i][0];
                    checkNotSame[0][1] = arr[i][1];
                    if ( flag2 == 0 )
                    {
                    usedNode[countTotalEdges][0] = arr[i][0];
                    usedNode[countTotalEdges][1] = arr[i][1];
                    node1OfEdge = i;
                    flag2 = 1;
                    countForTotalNodesUsed++;
                    draw();
                    }
                    else if ( flag2 == 1)
                    {
                        usedNode[countTotalEdges][2] = arr[i][0];
                        usedNode[countTotalEdges][3] = arr[i][1];
                        countTotalEdges++;
                        countForTotalNodesUsed++;
                        node2OfEdge = i;
                        edge[node1OfEdge][node2OfEdge] = 1;
                        edge[node2OfEdge][node1OfEdge] = 1;
                        valueInputFlag=1;
                        flag2 = 0;
                   draw();
                    }
                    }
                }

             }
    }
  }
 }

 }
}
void input(unsigned char key ,int x,int y)
{
    if (valueInputFlag==1)
    {
        switch(key)
        {
        case  48:
            costCharacterNumber++;
            costCharacters[costCharacterNumber] = '0';
            costCharacterRem[countTotalEdges-1][costCharacterNumber] = '0';
            costInt[costCharacterNumber] = 0;
            draw();
            break;
        case  49:
            costCharacterNumber++;
            costCharacters[costCharacterNumber] = '1';
            costCharacterRem[countTotalEdges-1][costCharacterNumber] = '1';
            costInt[costCharacterNumber] = 1;
            draw();
            break;
        case  50:
            costCharacterNumber++;
            costCharacters[costCharacterNumber] = '2';
            costCharacterRem[countTotalEdges-1][costCharacterNumber] = '2';
            costInt[costCharacterNumber] = 2;
            draw();
            break;
            case 51:
            costCharacterNumber++;
            costCharacters[costCharacterNumber] = '3';
            costCharacterRem[countTotalEdges-1][costCharacterNumber] = '3';
            costInt[costCharacterNumber] = 3;
            draw();
            break;
        case  52:
            costCharacterNumber++;
            costCharacters[costCharacterNumber] = '4';
            costCharacterRem[countTotalEdges-1][costCharacterNumber] = '4';
            costInt[costCharacterNumber] = 4;
            draw();
            break;
        case  53:
            costCharacterNumber++;
            costCharacters[costCharacterNumber] = '5';
            costCharacterRem[countTotalEdges-1][costCharacterNumber] = '5';
            costInt[costCharacterNumber] = 5;
            draw();
            break;
        case  54:
            costCharacterNumber++;
            costCharacters[costCharacterNumber] = '6';
            costCharacterRem[countTotalEdges-1][costCharacterNumber] = '6';
            costInt[costCharacterNumber] = 6;
            draw();
            break;
        case  55:
            costCharacterNumber++;
            costCharacters[costCharacterNumber] = '7';
            costCharacterRem[countTotalEdges-1][costCharacterNumber] = '7';
            costInt[costCharacterNumber] = 7;
            draw();
            break;
        case  56:
            costCharacterNumber++;
            costCharacters[costCharacterNumber] = '8';
            costCharacterRem[countTotalEdges-1][costCharacterNumber] = '8';
            costInt[costCharacterNumber] = 8;
            draw();
            break;
        case  57:
            costCharacterNumber++;
            costCharacters[costCharacterNumber] = '9';
            costCharacterRem[countTotalEdges-1][costCharacterNumber] = '9';
            costInt[costCharacterNumber] = 9;
            draw();
            break;
        case 13:

         for(int y=0; y<20;y++)
         {
         costCharacters[y]='\0';
         }
         sum = 0;
         for( int z=0;z<=costCharacterNumber;z++)
         {
             sum = pow(10,costCharacterNumber-z)*costInt[z]+sum;
         }
         cost[node1OfEdge][node2OfEdge] = sum;
         cost[node2OfEdge][node1OfEdge] = sum;
         costCharacterNumber = -1;
         valueInputFlag = 0 ;
            draw();
            break;





        }

    }
    if(key==32)
            exit(0);

}



int main(int argc, char **argv) {

	// init GLUT and create Window
	printf("\t\tINSTRUCTIONS\n\n1.Right Click to create a Node!\n2.Left Click to Select a Node\n3.Press Enter to input the Cost\n4. Press the Red Button to get Spanning Tree\n\n(If not able to create any edge please Re-run the application)\n\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300,50);
	glutInitWindowSize(size1,size1);
	glutDisplayFunc(draw);
	glutCreateWindow("Nodes");
	for( int q = 0 ; q<100;q++)
    {
        for( int l = 0 ; l<100;l++)
        {
            cost[q][l]=32767;
            edge[q][l] = 0;

        }
    }



	// register callbacks
	//glutDisplayFunc(renderScene);
	draw();
glutMouseFunc(renderScene);
glutKeyboardFunc(input);
	// enter GLUT event processing cycle
	glutMainLoop();


	return 1;
}
