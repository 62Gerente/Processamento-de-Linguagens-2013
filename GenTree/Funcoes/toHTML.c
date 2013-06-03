#include "toHTML.h"
#include "../Estruturas/Individuo.h"
#include "../Estruturas/Evento.h"

void toHTML (GHashTable* hash_individuos) {
    FILE *fp;

    fp = fopen("../HTML/index.html", "w");
    if(!fp){
        fprintf(stderr,"Erro a abrir o ficheiro index para escrita.\n");
        return;
    }
    
    int i,j;
    
    fprintf(fp,"<!DOCTYPE html>\n<html lang=\"pt\">\n<head>\n	\n	<meta charset=\"utf-8\">\n	<title>GenTree</title>\n\n	<link href=\"Layout/css/bootstrap.min.css\" rel=\"stylesheet\">\n <link href=\"Layout/css/bootstrap-responsive.min.css\" rel=\"stylesheet\">\n	<link href=\"Layout/css/style.css\" rel=\"stylesheet\">\n <link href=\"Layout/css/style-responsive.css\" rel=\"stylesheet\">\n	<link href=\"Layout/css/retina.css\" rel=\"stylesheet\">\n\n	<link rel=\"apple-touch-icon-precomposed\" sizes=\"144x144\" href=\"ico/apple-touch-icon-144-precomposed.png\">\n	<link rel=\"apple-touch-icon-precomposed\" sizes=\"114x114\" href=\"ico/apple-touch-icon-114-precomposed.png\">\n	<link rel=\"apple-touch-icon-precomposed\" sizes=\"72x72\" href=\"ico/apple-touch-icon-72-precomposed.png\">\n	<link rel=\"apple-touch-icon-precomposed\" href=\"ico/apple-touch-icon-57-precomposed.png\">\n	<link rel=\"shortcut icon\" href=\"ico/favicon.png\">\n\n</head>\n\n<body>\n	<div class=\"navbar\">\n		<div class=\"navbar-inner\" style=\"min-height:45px;\">\n <div class=\"container-fluid\">\n				<a class=\"btn btn-navbar\" data-toggle=\"collapse\" data-target=\".top-nav.nav-collapse,.sidebar-nav.nav-collapse\">\n <span class=\"icon-bar\"></span>\n					<span class=\"icon-bar\"></span>\n					<span class=\"icon-bar\"></span>\n				</a>\n <a class=\"brand\" href=\"index.html\"><span style=\"font-size:25px;\"><i class=\"fa-icon-sitemap\"></i><span style=\"color:#bdea74;\"> Gen</span>Tree</span></a>\n \n				<div class=\"nav-no-collapse header-nav\">\n\n				</div>\n				\n			</div>\n		</div>\n	</div>\n	<!-- start: Header -->\n	\n	<div class=\"container-fluid\">\n		<div class=\"row-fluid\">\n			\n			<!-- start: Content -->\n			<div id=\"content\" class=\"span12\">\n");

    GList* individuos = g_hash_table_get_values(hash_individuos);

    for(i=0;i<(int)g_list_length(individuos);i++){

        Individuo* ind = (Individuo*)g_list_nth_data(individuos,i);

        Individuo* conjugue = (Individuo*) g_hash_table_lookup(hash_individuos, &ind->idConjugue);
        Individuo* pai = (Individuo*)  g_hash_table_lookup(hash_individuos, &ind->idPai);
        Individuo* mae = (Individuo*)  g_hash_table_lookup(hash_individuos, &ind->idMae);


        fprintf(fp,"				<div class=\"box span12\" style=\"margin-left:0px;\">\n					<div class=\"box-header\">\n						<h2><i class=\"halflings-icon user\"></i><span class=\"break\"></span>");

        fprintf(fp,"<a name=\"id%d\"><a/>",ind->id);

        fprintf(fp,"%s || %d",ind->nome, ind->id);

        fprintf(fp,"</h2>\n						<div class=\"box-icon\">\n							<a href=\"#\" class=\"btn-minimize\"><i class=\"halflings-icon chevron-up\"></i></a>\n						</div>\n					</div>\n					<div class=\"box-content\" style=\"height:288px\">\n						<div class=\"row-fluid\">\n							<div class=\"span5\" style=\"\">\n								<img class=\"super-avatar\" src=\"");

        if(ind->foto != NULL){
            fprintf(fp,"%s",ind->foto);
        }else{
            if(ind->sexo==2){
                fprintf(fp,"Layout/img/fem.jpg");    
            }else{
                fprintf(fp,"Layout/img/male.jpg");
            }
        }

        fprintf(fp,"\"></img>\n								<h2><span><i class=\"halflings-icon info-sign\"></i><b> Informações</b></span></h2>\n								<div >\n									<p><span><b>Sexo: </b>");

        if(ind->sexo>0 && ind->sexo<3){
            if(ind->sexo==2){
                fprintf(fp,"Feminino");
            }else{
                fprintf(fp,"Masculino");
            }
        }else{
            fprintf(fp,"Desconhecido");
        }

        fprintf(fp,"</span></p>\n									<p><span><b>Data de Nascimento: </b>");

        if(ind->data_nascimento != NULL){
            fprintf(fp,"%s",ind->data_nascimento);    
        }else{
            fprintf(fp,"Desconhecida");
        }

        fprintf(fp,"</span></p>\n									<p><span><b>Data de Falecimento: </b>");

        if(ind->data_morte != NULL){
            fprintf(fp,"%s",ind->data_morte);    
        }else{
            fprintf(fp,"Desconhecida");
        }

        fprintf(fp,"</span></p>\n								</div>\n							</div>\n							<div class=\"span4\">\n								<h2><span><i class=\"halflings-icon home\"></i><b> Filho de</b></span></h2>\n								<a href=\"#");

        if(pai != NULL){
            fprintf(fp,"id%d",pai->id);
        }

        fprintf(fp,"\"><div style=\"padding-top:5px;\">\n									<img class=\"mini-avatar\" src=\"");

        if(pai != NULL && pai->foto != NULL){
            fprintf(fp,"%s",pai->foto);
        }else{
            fprintf(fp,"Layout/img/male.jpg");
        }

        fprintf(fp,"\"></img>\n									<p><span>");

        if(pai != NULL && pai->nome != NULL){
            fprintf(fp,"%s",pai->nome);
        }else{
            fprintf(fp,"Desconhecido");
        }

        fprintf(fp,"</span></p>\n								</div></a>\n								<a href=\"#");

        if(mae != NULL){
            fprintf(fp,"id%d",mae->id);
        }

        fprintf(fp,"\"><div style=\"padding-top:10px;\">\n									<img class=\"mini-avatar\" src=\"");

        if(mae != NULL && mae->foto != NULL){
            fprintf(fp,"%s",mae->foto);
        }else{
            fprintf(fp,"Layout/img/fem.jpg");
        }

        fprintf(fp,"\"></img>\n									<p><span>");

        if(mae != NULL && mae->nome != NULL){
            fprintf(fp,"%s",mae->nome);
        }else{
            fprintf(fp,"Desconhecida");
        }

        fprintf(fp,"</span></p>\n								</div></a>\n							</div>\n							<div class=\"span3\">\n								<h2><span><i class=\"halflings-icon heart\"></i><b> Casado com</b></span></h2>\n								<a href=\"#");

        if(conjugue != NULL){
            fprintf(fp,"id%d",conjugue->id);
        }

        fprintf(fp,"\"><div style=\"padding-top:5px;\">\n									<img class=\"mini-avatar\" src=\"");

        if(conjugue != NULL){
            if(conjugue->foto != NULL){
                fprintf(fp,"%s",conjugue->foto);
            }else{
                if(conjugue->sexo == 2){
                    fprintf(fp,"%s","Layout/img/fem.jpg"); 
                }else if(conjugue->sexo == 1){
                    fprintf(fp,"%s","Layout/img/male.jpg"); 
                }else{
                    if(ind->sexo == 2){
                        fprintf(fp,"%s","Layout/img/male.jpg"); 
                    }else{
                        fprintf(fp,"%s","Layout/img/fem.jpg"); 
                    }
                }
            }
        }else{
            if(ind->sexo == 2){
                fprintf(fp,"%s","Layout/img/male.jpg"); 
            }else{
                fprintf(fp,"%s","Layout/img/fem.jpg"); 
            }
        }

        fprintf(fp,"\"></img>\n									<p><span>");

        if(conjugue != NULL){
            if(conjugue->nome != NULL){
                fprintf(fp,"%s",conjugue->nome);
            }else{
                if(conjugue->sexo == 2){
                    fprintf(fp,"%s","Desconhecida"); 
                }else if(conjugue->sexo == 1){
                    fprintf(fp,"%s","Desconhecido"); 
                }else{
                    if(ind->sexo == 2){
                        fprintf(fp,"%s","Desconhecido"); 
                    }else{
                        fprintf(fp,"%s","Desconhecida"); 
                    }
                }
            }
        }else{
            if(ind->sexo == 2){
                fprintf(fp,"%s","Desconhecido"); 
            }else{
                fprintf(fp,"%s","Desconhecida"); 
            }
        }

        fprintf(fp,"</span></p>\n								</div></a>\n								<div style=\"padding-top:10px;\">\n									<p><span><b>Data Casamento: </b>");


        if(ind->data_casamento != NULL){
            fprintf(fp,"%s",ind->data_casamento);    
        }else{
            if(conjugue != NULL && conjugue->data_casamento != NULL){
                fprintf(fp,"%s",conjugue->data_casamento);    
            }else{
                fprintf(fp,"Desconhecida");
            }
        }

        fprintf(fp,"</span></p>\n								</div>\n							</div>\n						</div>");

        fprintf(fp,"<div class=\"row-fluid\">\n							<div class=\"span3\" style=\"\">\n								<h2><span><i class=\"halflings-icon leaf\"></i><b> Filhos</b></span></h2>\n								<div class=\"span12\" style=\"height:118px;overflow-y:scroll;\">");
        
    
        int nr =0; 
        for(j=0;j<(int)g_list_length(individuos);j++){

            Individuo* filho = (Individuo*)g_list_nth_data(individuos,j);
        
        Individuo* fpai = (Individuo*)  g_hash_table_lookup(hash_individuos, &filho->idPai);
        Individuo* fmae = (Individuo*)  g_hash_table_lookup(hash_individuos, &filho->idMae);


            if((fpai != NULL && fpai->id == ind->id) || (fmae != NULL && fmae->id == ind->id)){
                
                fprintf(fp,"<a href=\"#");
                fprintf(fp,"id%d",filho->id);

                fprintf(fp,"\"><div style=\"padding-top:");
                
                if(nr==0){
                    fprintf(fp,"%d",5);
                }else{
                    fprintf(fp,"%d",10);
                }

                fprintf(fp,"px;\">\n										<img class=\"mini-avatar\" src=\"");

                if(filho != NULL && filho->foto != NULL){
                    fprintf(fp,"%s",filho->foto);
                }else{
                    fprintf(fp,"Layout/img/male.jpg");
                }

                fprintf(fp,"\"></img>\n										<p><span>");

                if(filho != NULL && filho->nome != NULL){
                    fprintf(fp,"%s",filho->nome);
                }else{
                    fprintf(fp,"Desconhecido");
                }

                fprintf(fp,"</span></p>\n									</div></a>");

                nr++;
            }
        
        }

        fprintf(fp,"</div>\n							</div>\n							<div class=\"span5\" style=\"\">\n								<h2><span><i class=\"halflings-icon film\"></i><b> Histórias</b></span></h2>\n								<div class=\"span12\" style=\"height:118px;overflow-y:scroll;margin-left:0px;\">\n									<ul class=\"chat\">");

    
        GList* historias = ind->historias;

        for(j=0;j<(int)g_list_length(historias);j++){
            
            char* historia = (char*)g_list_nth_data(historias,j);

            FILE *hst;

            hst = fopen(historia,"r");
            
            if(!hst){
                fprintf(stderr,"Erro ao abrir a história %s para leitura.\n",historia);
                continue;
            }

            fprintf(fp,"										<li class=\"\">\n											<span class=\"message\">\n												<span class=\"text\">");

            char linha[512];
            while(fgets(linha,512,hst) != NULL){
                fprintf(fp,"%s",linha);
            }


            fprintf(fp,"												</span>\n											</span>	                                  \n										</li>");

            fclose(hst);
        }

        fprintf(fp,"</ul>\n								</div>\n							</div>\n							<div class=\"span4\" style=\"\">\n								<h2><span><i class=\"halflings-icon time\"></i><b> Eventos</b></span></h2>\n								<div class=\"span12\" style=\"height:118px;overflow-y:scroll;;margin-left:0px;\">\n									<ul class=\"chat\">");

        GList* eventos = ind->eventos;

        for(j=0;j<(int)g_list_length(eventos);j++){
            
            Evento* evento = (Evento*)g_list_nth_data(eventos,j);

            fprintf(fp,"<li class=\"\">\n											<span class=\"message\">\n												<span class=\"from\">");

            if(evento->nome != NULL){
                fprintf(fp,"%s",evento->nome);
            }else{
                fprintf(fp,"Desconhecido");
            }

            fprintf(fp,"</span>\n												<span class=\"time\">");

            if(evento->data != NULL){
                fprintf(fp,"%s",evento->data);
            }else{
                fprintf(fp,"Desconhecida");
            }

            fprintf(fp,"</span>\n												<span class=\"text\">");

            if(evento->descricao != NULL){
                fprintf(fp,"%s",evento->descricao);
            }else{
                fprintf(fp,"Desconhecido");
            }

            fprintf(fp,"</span>\n											</span>	                                  \n										</li>");


        }

        fprintf(fp,"</ul>\n								</div>\n							</div>\n						</div>\n					</div>\n				</div>\n");

    }


    fprintf(fp,"</div>\n			<!-- end: Content -->\n			\n		<!-- start: Widgets Area -->\n		<div id=\"widgets-area\" class=\"span2 hidden-tablet            hidden-phone\">\n \n		</div>\n		<!-- end: Widgets Area -->\n\n		<a id=\"widgets-area-button\" class=\"hidden-tablet hidden-phone open\"><i            class=\"fa-icon-reorder\"></i></a>				\n	</div><!--/fluid-row-->\n				\n		<div class=\"clearfix\"></div>\n		\n            <footer>\n <p>\n				<span style=\"text-align:left;float:left\">GenTree 2013</span>\n				<span class=\"hidden-phone\"            style=\"text-align:right;float:right;margin-right:20px;\">Processamento de Linguagens</span>\n			</p>\n\n		</footer>\n				\n </div><!--/.fluid-container-->\n\n	<!-- start: JavaScript-->\n\n		<script src=\"Layout/js/jquery-1.9.1.min.js\"></script>\n	<script src=\"Layout/js/jquery-migrate-1.0.0.min.js\"></script>\n	\n		<script src=\"Layout/js/jquery-ui-1.10.0.custom.min.js\"></script>\n	\n		<script src=\"Layout/js/jquery.ui.touch-punch.js\"></script>\n	\n		<script src=\"Layout/js/modernizr.js\"></script>\n	\n		<script src=\"Layout/js/bootstrap.min.js\"></script>\n	\n		<script src=\"Layout/js/jquery.cookie.js\"></script>\n	\n		<script src='Layout/js/fullcalendar.min.js'></script>\n	\n		<script src='Layout/js/jquery.dataTables.min.js'></script>\n\n		<script src=\"Layout/js/excanvas.js\"></script>\n	<script src=\"Layout/js/jquery.flot.js\"></script>\n	<script src=\"Layout/js/jquery.flot.pie.js\"></script>\n	<script src=\"Layout/js/jquery.flot.stack.js\"></script>\n	<script src=\"Layout/js/jquery.flot.resize.min.js\"></script>\n		\n		<script src=\"Layout/js/gauge.min.js\"></script>\n\n		<script src=\"Layout/js/jquery.chosen.min.js\"></script>\n	\n		<script src=\"Layout/js/jquery.uniform.min.js\"></script>\n		\n		<script src=\"Layout/js/jquery.cleditor.min.js\"></script>\n	\n		<script src=\"Layout/js/jquery.noty.js\"></script>\n	\n		<script src=\"Layout/js/jquery.elfinder.min.js\"></script>\n	\n		<script src=\"Layout/js/jquery.raty.min.js\"></script>\n	\n		<script src=\"Layout/js/jquery.iphone.toggle.js\"></script>\n	\n		<script src=\"Layout/js/jquery.uploadify-3.1.min.js\"></script>\n	\n		<script src=\"Layout/js/jquery.gritter.min.js\"></script>\n	\n		<script src=\"Layout/js/jquery.imagesloaded.js\"></script>\n	\n		<script src=\"Layout/js/jquery.masonry.min.js\"></script>\n	\n		<script src=\"Layout/js/jquery.knob.modified.js\"></script>\n	\n		<script src=\"Layout/js/jquery.sparkline.min.js\"></script>\n	\n		<script src=\"Layout/js/counter.js\"></script>\n	\n		<script src=\"Layout/js/raphael.2.1.0.min.js\"></script>\n	<script src=\"Layout/js/justgage.1.0.1.min.js\"></script>\n	\n		<script src=\"Layout/js/retina.js\"></script>\n\n		<script src=\"Layout/js/core.min.js\"></script>\n \n		<script src=\"Layout/js/charts.js\"></script>\n	\n		<script src=\"Layout/js/custom.js\"></script>\n	<!-- end: JavaScript-->\n \n</body>\n</html>\n");

    fclose(fp);
}
