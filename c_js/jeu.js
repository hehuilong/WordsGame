var x,y,n; //pour taille et nombre de mots
var h,m,s; //pour le presentation du temps
var dh,dm,ds; //delta de temps
var prenum; //pour memoriser le dernier click
var response; //pour recuperer le reponse du serveur
var trouveflags=new Array(8); //pour memoriser si le mot a ete choisi
var trouve; //pour memoiriser le nombre de mot trouve
var timehandler; //pour arreter l'horloge
var lowestscore = 999999 ; //the lowest score in the ranklist
var niveau; //memoiriser le niveau
var grille;
var liste;

//for alert with more effect
function sAlert(titleStr,str){
    var msgw,msgh,bordercolor;
    msgw=250;//dialog hight
    msgh=400;//dialog width
    titleheight=25 
    bordercolor="#336699";
    titlecolor="#99CCFF";
   
    var sWidth,sHeight;
    sWidth=document.body.offsetWidth;
    sHeight=screen.height;

    var bgObj=document.createElement("div");
    bgObj.setAttribute('id','bgDiv');
    bgObj.style.position="absolute";
    bgObj.style.top="0";
    bgObj.style.background="#777";
    bgObj.style.filter="progid:DXImageTransform.Microsoft.Alpha(style=3,opacity=25,finishOpacity=75";
    bgObj.style.opacity="0.6";
    bgObj.style.left="0";
    bgObj.style.width=sWidth + "px";
    bgObj.style.height=sHeight + "px";
    bgObj.style.zIndex = "10000";
    document.body.appendChild(bgObj);
   
    var msgObj=document.createElement("div")
    msgObj.setAttribute("id","msgDiv");
    msgObj.setAttribute("align","center");
    msgObj.style.background="white";
    msgObj.style.border="1px solid " + bordercolor;
    msgObj.style.position = "absolute";
    msgObj.style.left = "57%";
    msgObj.style.top = "30%";
    msgObj.style.font="12px/1.6em Verdana, Geneva, Arial, Helvetica, sans-serif";
    msgObj.style.marginLeft = "-225px" ;
    msgObj.style.marginTop = -75+document.documentElement.scrollTop+"px";
    msgObj.style.width = msgw + "px";
    msgObj.style.height =msgh + "px";
    msgObj.style.textAlign = "center";
    msgObj.style.lineHeight ="25px";
    msgObj.style.zIndex = "10001";

   var title=document.createElement("h4");
   title.setAttribute("id","msgTitle");
   title.setAttribute("align","left");
   title.style.margin="0";
   title.style.padding="3px";
   title.style.background=bordercolor;
   title.style.filter="progid:DXImageTransform.Microsoft.Alpha(startX=20, startY=20, finishX=100, finishY=100,style=1,opacity=75,finishOpacity=100);";
   title.style.opacity="0.75";
   title.style.border="1px solid " + bordercolor;
   title.style.height="18px";
   title.style.font="12px Verdana, Geneva, Arial, Helvetica, sans-serif";
   title.style.color="white";
   title.style.cursor="pointer";
   title.innerHTML=titleStr;
   title.onclick=function(){
        document.body.removeChild(bgObj);
        document.getElementById("msgDiv").removeChild(title);
        document.body.removeChild(msgObj);
        }
   document.body.appendChild(msgObj);
   document.getElementById("msgDiv").appendChild(title);
   var txt=document.createElement("div");
   //txt.style.margin="1em 0"
   txt.style.position="relative";
   txt.style.top="15%";
   txt.style.left="25%";
   txt.setAttribute("id","msgTxt");
   txt.innerHTML=str;
   document.getElementById("msgDiv").appendChild(txt);
}

//function pour get xml ajax object
function getXmlHttpObject(){
   var xmlHttp;
   var e;
   try{
       xmlHttp=new XMLHttpRequest();
   }
   catch (e){
       try{
           xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
       }
       catch (e){
           try{
           mlHttp=new ActiveXObject("Microsoft.XMLHTTP");
           }
           catch (e){
              alert("AJAX not supportted by your brower");
              return false;
           }
       }
    }
	return xmlHttp;
 }

var xmlHttp=getXmlHttpObject();

//functions pour obtenir le score le plus bas
function getlowestscore(){
    var url="./cgi-bin/lowestscore.cgi";
    xmlHttp.open("GET",url,true);
    xmlHttp.onreadystatechange=memoryLowestScore;
    xmlHttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    xmlHttp.send();
}

function memoryLowestScore(){
    if(xmlHttp.readyState==4){
        lowestscore=xmlHttp.responseText;
        lowestscore=lowestscore.split(": ");
        lowestscore=lowestscore[1]*1;
        //alert(lowestscore);
        rankme();
    }
}

//function pour comparer le score avec ranklist et renouveller le ranklist
function rankme(){
    var finalscore=calScore();
    if(finalscore<=lowestscore){
        alert("Good job! Your score:"+finalscore+" This time you didn't get into the ranklist. Come on , challenge them!");
    }
    else{
        var name;
        name=prompt("Your score:"+finalscore+"; Congrats! Please leave your name on the ranklist (name length<=30 ):","");
        //alert(name.length+" "+name);
        if(name==null)return;
        while(name==""||name.length>30){
            name=prompt("Please enter your name to be shown on the ranklist (name length<=30):","");
            if(name==null)return;
        }
        gotoranklist(name,finalscore);
    }
}

//function pour inserer nouveau score et nom dans le ranklist
function gotoranklist(name,score){
    var url="./cgi-bin/insertrank.cgi";
    xmlHttp.open("POST",url,true);
    xmlHttp.onreadystatechange=null; //necessaire , sinon ca == function ancienne
    xmlHttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    var content = name+" : "+score;
    xmlHttp.send(content);
}

//functions pour obtenir le ranklist
function ranklist(){
    var url="./cgi-bin/showrank.cgi";
    xmlHttp.open("GET",url,true);
    xmlHttp.onreadystatechange=showRank;
    xmlHttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    xmlHttp.send();
}

function showRank(){
    if(xmlHttp.readyState==4){
        var rank=xmlHttp.responseText;
	var txt="<table border=\"0\">";
	rank=rank.split("#");
	var i;
	for(i=0;i<10;i++){
		var t=rank[i];
		//alert(t);
		t=t.split(":");
		txt+="<tr>";
		txt+="<td align=\"left\">";
		txt+=t[0];
		txt+="</td>";
		txt+="<td>:";
		txt+="</td>";
		txt+="<td align=\"right\">";
		txt+=t[1];
		txt+="</td>";
		txt+="</tr>";
	}
	txt+="</table>"
        sAlert("Rank List",txt);
    }
}

//functions pour generer un jeu d'un niveau
function genererJeu(level){
    niveau=level;
    if(level==1){
        //cadre.style.width=340;
        x=y=8;
        n=4;
    }
    else if(level==2){
        //cadre.style.width=420;
        x=y=10;
        n=6;
    }
    else{
        //cadre.style.width=580;
        x=y=15;
        n=8;
    }

    grille=document.getElementById("grille");
    liste=document.getElementById("listemots");
    grille.innerHTML='';
    liste.innerHTML='';
    grille.innerHTML='<div id="loading">Loading...</div>';

    var url="./cgi-bin/generer.cgi?level="+level;
    xmlHttp.open("GET",url,true);
    xmlHttp.onreadystatechange=showGame;
    xmlHttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    //var content="level=1";
    xmlHttp.send();
}

function showGame(){
   //si le serveur retourne la reponse
   if(xmlHttp.readyState==4){
      //show the grille and liste
      grille.innerHTML='';
      liste.innerHTML='<div id="time"></div>';
	  response=xmlHttp.responseText;
	  response=response.split("#");
	  var i,j;
	  for(i=0;i<x;i++){
        grille.innerHTML+='<div class="ligne">';
        for(j=0;j<y;j++){
            grille.innerHTML+='<div onclick="test('+(i*y+j)+')" class="element" id="element'+(i*y+j)+'">'+response[0][i*y+j]+'</div>';
        }
        grille.innerHTML+='</div>';
	  }
	  for(i=1;i<=n;i++){
        liste.innerHTML+='<div id="list' +(i-1)+ '" class="list">'+response[i]+'</div>';
        trouveflags[i]=false;
      }
      prenum=-1;//pour memoriser le dernier click
      trouve=0;//nombre trouve
      //le temps de debut
      var start=new Date();
      h=start.getHours();
      m=start.getMinutes();
      s=start.getSeconds();
      startTime();
   }
}

//function pour generer l'horloge
function startTime(){
    var now=new Date();
    dh=now.getHours()-h;
    dm=now.getMinutes()-m;
    ds=now.getSeconds()-s;
    if(ds<0){
        ds+=60;
        dm-=1;
    }
    if(dm<0){
        dm+=60;
        dh-=1;
    }
    // add a zero in front of numbers<10
    var dhh=checkTime(dh);
    var dmm=checkTime(dm);
    var dss=checkTime(ds);
    document.getElementById('time').innerHTML=dhh+":"+dmm+":"+dss;
    timehandler=setTimeout('startTime()',500);
}

function checkTime(i){
    if (i<10){
        i="0" + i;
    }
    return i;
}

//function pour tester les choix de mot
function test(num){
    var id="element"+num;
    //pour changer le border en temps que click
    if(prenum!=-1){
        preid="element"+prenum;
        document.getElementById(preid).style.borderColor="";
    }
    document.getElementById(id).style.borderColor="red";
    //pour tester si le mot est dans la liste
    if(prenum!=-1){
        var prex,prey,nowx,nowy,dx,dy,parx,pary;
        prex=Math.floor(prenum/y);
        prey=prenum%y;
        nowx=Math.floor(num/y);
        nowy=num%y;
        dx=nowx-prex;
        dx=dx<0?-dx:dx;
        dy=nowy-prey;
        dy=dy<0?-dy:dy;
        //alert(""+prex+"#"+prey+"#"+nowx+"#"+nowy);
        //pour recuperer le mot choisi et les num
        var choisi;
        var numarray=new Array();
        if(dx==0||dy==0||dx==dy){//si les deux sont en meme droite
            dx=(prex>nowx)?-1:1;
            dx=(prex==nowx)?0:dx;
            dy=(prey>nowy)?-1:1;
            dy=(prey==nowy)?0:dy;
            parx=prex;
            pary=prey;
            choisi="";//le mot choisi par l'utilisateur
            var count=0;
            while(!(parx==nowx&&pary==nowy)){
                choisi+=response[0][parx*y+pary];
                numarray[count]=parx*y+pary;
                parx+=dx;
                pary+=dy;
                count++;
            }
            choisi+=response[0][num];
            numarray[count]=parx*y+pary;
            //alert(choisi);
            //tester si le mot est dans la liste
            var i;
            for(i=1;i<response.length;i++){
                if(trouveflags[i]==false && ( choisi.toLowerCase()==response[i].toLowerCase()||choisi.split("").reverse().join("").toLowerCase()==response[i].toLowerCase() )){
                    trouve+=1;
                    trouveflags[i]=true;
                    //alert(trouve+"#"+n);
                    //changer le couleur
                    var j;
                    for(j in numarray){
                        document.getElementById("element"+numarray[j]).style.background="#C0D9D9";
                    }
                    document.getElementById("list"+(i-1)).style.background="#C0D9D9";
                    if(trouve>=n){
                        fin();
                    }
                    break;
                }
            }
        }
    }
    prenum=num;
}

//function pour calculer le score
function calScore(){
    return (1000-(dh*60*60+dm*60+ds))*niveau;
}

//function pour traiter les donnees a la fin du jeu
function fin(){
    //response=[];
    clearTimeout(timehandler);
    getlowestscore();
}


