#include <stdio.h>     
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int outputFileLatex, outputFileHtml , inputFile,  output=0; //0-Ambos, 1-Latex, 2-Html
    int input =0;

    if(argc < 2){   // Nenhum argumento = ERRO

        fprintf(stderr, "Erro, introduza o path do ficheiro de input.\n") ;
        exit(-1);

    }else if(argc==2){  // 1 Argumento 
        if( strcmp(argv[1],"--latex")==0 || strcmp(argv[1],"--html")==0){ // É opçao = ERRO

            fprintf(stderr, "Erro, introduza o path do ficheiro de input.\n") ;
            exit(-1);

        }else{  // Abre argumento e gera Latex e Html

            inputFile = open(argv[1],O_RDONLY);
            input=1;
            outputFileLatex = open("Latex.tex",O_WRONLY|O_CREAT,0644);
            outputFileHtml = open("Html.html",O_WRONLY|O_CREAT,0644);

        }

    }else if(argc==3){ // 2 Argumentos

         if( strcmp(argv[1],"--latex")==0 ){  // Abre argumento e gera Latex
            output=1;
        
            inputFile = open(argv[2],O_RDONLY);
            input =1;
            outputFileLatex = open("Latex.tex",O_WRONLY|O_CREAT,0644);

         }else if( strcmp(argv[1],"--html")==0 ){ // Abre argumento e gera Html
             output=2;

             inputFile = open(argv[2],O_RDONLY);
             input=2;
             outputFileHtml = open("Html.html",O_WRONLY|O_CREAT,0644);

         }else{ // Abre argumento e geram Latex e Html com o mesmo nome
             
            inputFile = open(argv[1],O_RDONLY);
            input =1;

            char auxl[strlen(argv[2])+4];
            char auxh[strlen(argv[2])+5];

            strcpy(auxl,argv[2]);
            strcpy(auxh,argv[2]);

            strcat(auxl,".tex");
            strcat(auxh,".html");
            
            outputFileLatex = open(auxl,O_WRONLY|O_CREAT,0644);
            outputFileHtml = open(auxh,O_WRONLY|O_CREAT,0644);

         }
       
    }else if(argc==4){ // 3 Argumentos

         if( strcmp(argv[1],"--latex")==0 ){ // Abre argumento e gera Latex
            output=1;
        
            inputFile = open(argv[2],O_RDONLY);
            input=2;
            outputFileLatex = open(argv[3],O_WRONLY|O_CREAT,0644);

         }else if( strcmp(argv[1],"--html")==0 ){ // Abre argumento e gera Html

             output=2;

             inputFile = open(argv[2],O_RDONLY);
             input=2; 
             outputFileHtml = open(argv[3],O_WRONLY|O_CREAT,0644);

         }else{ // Abre argumento e gera Html e Latex
             
            inputFile = open(argv[1],O_RDONLY);
            input=1;

            outputFileLatex = open(argv[2],O_WRONLY|O_CREAT,0644);
            outputFileHtml = open(argv[3],O_WRONLY|O_CREAT,0644);

         }
    }else{ // Mais de 3 argumentos = ERRO
            fprintf(stderr, "Número de argumentos inválido, consulte o manual da ferramenta.\n") ;
            exit(-1);
    }


    // Verificar erros de leitura
    if(inputFile<0) {
        fprintf(stderr,"Ocorreu um erro na leitura do ficheiro de input.\n") ;
        exit(-1);
    }
    
    // Verificar erros de escrita
    if((output==1 && outputFileLatex <0) || (output==2 && outputFileHtml <0)){
        fprintf(stderr,"Ocorreu um erro na escrita de um ficheiro de output.\n") ;
        exit(-1);
    }

    if(output<2){
        int pidLatex= fork();
        if(!pidLatex){
            dup2(inputFile,0);
            dup2(outputFileLatex,1);
            fprintf(stderr,"Ficheiro latex gerado com êxito.\n") ;
            execlp("./latex","./latex",NULL);
            exit(0);
        }
    }
    wait(0);
    inputFile = open(argv[input],O_RDONLY);


    if(output==0 || output==2){
        int pidHtml= fork();
        if(!pidHtml){
            dup2(inputFile,0);
            dup2(outputFileHtml,1);
	    fprintf(stderr,"Ficheiro html gerado com êxito.\n") ;
	    execlp("./html","./html",NULL);                       
            exit(0);
        }
    }
    wait(0);
    close(inputFile) ;

    return 0;
}
