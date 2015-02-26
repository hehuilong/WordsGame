var MAX_WORDS = 8;
var x,y,n; //pour taille et nombre de mots
var h,m,s; //pour le presentation du temps
var dh,dm,ds; //delta de temps
var prenum; //pour memoriser le dernier click
var response; //the response of server
var trouveflags=new Array(MAX_WORDS); //flag indicating if the words are chosen
var trouve; //the number of words found
var timehandler; //for controlling clock
var niveau; //the level
var grille;
var liste;
var wordsGrid; // 1D array storing the words grid
var bitMap; // 2D array storing the words occupation info
var wordsList; // array storing the list of words
var searchOrder = new Array(MAX_WORDS); // searching order of positions in the grid for every word
var direction = new Array(MAX_WORDS);   // searching order of directions of word in the grid
var DIREC = [[1,1], [0,1], [0,-1], [1,-1], [-1, 0], [-1, 1], [1,0], [-1, -1]];
var wordsNum; // number of words
var height, width; // grid height and width
var gridNum; // squares number in the grid
var highestScore = 0;
var scoreDom; // div showing the score

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

//functions pour generer un jeu d'un niveau
function genererJeu(level){
	clearTimeout(timehandler);
    niveau=level;
    if(level==1){
        //cadre.style.width=340;
        x=y=6;
        n=3;
    }
    else if(level==2){
        //cadre.style.width=420;
        x=y=10;
        n=6;
    }
    else{
        //cadre.style.width=580;
        x=y=15;
        n=12;
    }

    grille=document.getElementById("grille");
    liste=document.getElementById("listemots");
    grille.innerHTML='';
    liste.innerHTML='';
    grille.innerHTML='<div id="loading">Loading...</div>';

    var url="./get_words.php?num="+n+"&length="+x+"&r="+Math.random();
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
      liste.innerHTML='<div id="time"></div>';
	  response=xmlHttp.responseText;
	  
	  wordsList=response.split("#");
	  //sAlert("Debug",wordsList);
	  
	  for(i=0;i<n;i++){
        liste.innerHTML+='<div id="list' +i+ '" class="list">'+wordsList[i]+'</div>';
        trouveflags[i]=false;
      }
	  
	  generateGrid(x, y);
	  grille.innerHTML = "";
	  var i,j;
	  for(i=0;i<x;i++){
        grille.innerHTML+='<div class="ligne">';
        for(j=0;j<y;j++){
            grille.innerHTML+='<div onclick="test('+(i*y+j)+')" class="element" id="element'+(i*y+j)+'">'+wordsGrid[i*y+j]+'</div>';
        }
        grille.innerHTML+='</div>';
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
   else{
	   grille.innerHTML='Generating Words Grid. Please Wait...';
   }
}

// random integer in [min, max]
function randomInt (min, max) {
    return Math.round(Math.random() * (max - min) + min);
}

function generateGrid(h, w){
	wordsNum = wordsList.length;
	height = h;
	width = w;
	gridNum = height*width;
	wordsGrid = new Array(gridNum);
	bitMap = new Array(width);
	var i,j;
	for(i=0; i<gridNum; i++) wordsGrid[i] = '0';
	for(i=0; i<width; i++){
		bitMap[i] = new Array(height);
		for(j=0; j<height; j++){
			bitMap[i][j] = 0;
		}
	}
	// generate random searching sequences
	for(i=0; i<wordsNum; i++){
		searchOrder[i] = new Array(gridNum);
		direction[i] = new Array(8); // 8 directions
		for(j=0; j<gridNum; j++){
			searchOrder[i][j] = j;
			var ex = randomInt(0, j);
			var tmp = searchOrder[i][j];
			searchOrder[i][j] = searchOrder[i][ex];
			searchOrder[i][ex] = tmp;
		}
		for(j=0; j<8; j++){
			direction[i][j] = j;
			var ex = randomInt(0, j);
			var tmp = direction[i][j];
			direction[i][j] = direction[i][ex];
			direction[i][ex] = tmp;
		}
	}
	// DFS the places of words
	if(!placeWord(0)) alert("Seems there is some bugs :(");
	// fill in arbitrary letter in the other squares
	for(i=0; i<height; i++){
		for(j=0; j<width; j++){
			if(bitMap[i][j] == 0){
				wordsGrid[i*width+j] = String.fromCharCode(randomInt("a".charCodeAt(0), "z".charCodeAt(0))).charAt(0);
			}
		}
	}
}

function placeWord(index){
	if(index == wordsNum) return true;
	var word = wordsList[index];
	var pos; // position and direction
	var dir;
	var i, j;
	for(i=0; i<gridNum; i++){
		pos = searchOrder[index][i];
		for(j=0; j<8; j++){ // all directions!
			dir = direction[index][j];
			if(!isValidePlace(word, pos, DIREC[dir])){
				continue;
			}else{
				// write the word in the grid
				writeWord(word, pos, DIREC[dir]);
				// place next word
				if(placeWord(index+1)){
					return true;
				}else{
					//backtracking, erase the word placed and continue
					eraseWord(word, pos, DIREC[dir]);
				}
			}
		}
	}
	return false;
}

function eraseWord(word, pos, dir){
	var startLine = Math.floor(pos/width);
	var startCol = pos % width;
	var length = word.length;
	var endLine = startLine + dir[0]*(length-1);
	var endCol = startCol + dir[1]*(length-1);
	var line = startLine;
	var col = startCol;
	while(line!=endLine+dir[0]){
		bitMap[line][col] --;
		line += dir[0];
		col += dir[1];
	}
	// in case dir[0] == 0
	while(col!=endCol+dir[1]){
		bitMap[line][col] --;
		line += dir[0];
		col += dir[1];
	}
	return true;
}

function writeWord(word, pos, dir){
	var startLine = Math.floor(pos/width);
	var startCol = pos % width;
	var length = word.length;
	var endLine = startLine + dir[0]*(length-1);
	var endCol = startCol + dir[1]*(length-1);
	var line = startLine;
	var col = startCol;
	while(line!=endLine+dir[0]){
		bitMap[line][col] ++;
		wordsGrid[line*width+col] = word.charAt(Math.abs(line-startLine));
		line += dir[0];
		col += dir[1];
	}
	// in case dir[0] == 0
	while(col!=endCol+dir[1]){
		bitMap[line][col] ++;
		wordsGrid[line*width+col] = word.charAt(Math.abs(col-startCol));
		line += dir[0];
		col += dir[1];
	}
	return true;
}

function isValidePlace(word, pos, dir){
	var startLine = Math.floor(pos/width);
	var startCol = pos % width;
	var length = word.length;
	var endLine = startLine + dir[0]*(length-1);
	var endCol = startCol + dir[1]*(length-1);
	if(endLine<0 || endLine>height-1 || endCol<0 || endCol>width-1) return false;
	var line = startLine;
	var col = startCol;
	while(line!=endLine+dir[0]){
		if(bitMap[line][col]>0 && wordsGrid[line*width+col] != word.charAt(Math.abs(line-startLine))) return false;
		line += dir[0];
		col += dir[1];
	}
	// in case dir[0] == 0
	while(col!=endCol+dir[1]){
		if(bitMap[line][col]>0 && wordsGrid[line*width+col] != word.charAt(Math.abs(col-startCol))) return false;
		line += dir[0];
		col += dir[1];
	}
	return true;
}

//function for generating clock
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

//function for testing the choice of word
function test(num){
    var id="element"+num;
    //change the appearance of square clicked
    if(prenum!=-1){
        preid="element"+prenum;
        document.getElementById(preid).style.borderColor="";
		document.getElementById(preid).style.borderStyle="dotted";
    }
    document.getElementById(id).style.borderColor="red";
	document.getElementById(id).style.borderStyle="double";
    //test if the word chosen is in the list of word to find
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
        if(dx==0||dy==0||dx==dy){//if the two are on the same straight line
            dx=(prex>nowx)?-1:1;
            dx=(prex==nowx)?0:dx;
            dy=(prey>nowy)?-1:1;
            dy=(prey==nowy)?0:dy;
            parx=prex;
            pary=prey;
            choisi="";//the word chosen by player
            var count=0;
            while(!(parx==nowx&&pary==nowy)){
                choisi+=wordsGrid[parx*y+pary];
                numarray[count]=parx*y+pary;
                parx+=dx;
                pary+=dy;
                count++;
            }
            choisi+=wordsGrid[num];
            numarray[count]=parx*y+pary;
            //alert(choisi);
            //test if the word chosen is in the list
            var i;
            for(i=0;i<wordsList.length;i++){
                if(trouveflags[i]==false && ( choisi.toLowerCase()==wordsList[i].toLowerCase()||choisi.split("").reverse().join("").toLowerCase()==wordsList[i].toLowerCase() )){
                    trouve+=1;
                    trouveflags[i]=true;
                    //alert(trouve+"#"+n);
                    //change colour
                    var j;
                    for(j in numarray){
                        document.getElementById("element"+numarray[j]).style.background="#C0D9D9";
                    }
                    document.getElementById("list"+(i)).style.background="#C0D9D9";
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

//function for calculating the score
function calScore(){
    return (1000-(dh*60*60+dm*60+ds))*niveau;
}

//function called in the end of game
function fin(){
	clearTimeout(timehandler);
	var score = calScore();
	alert("You Win! Score: "+score);
	if(score > highestScore){
		highestScore = score;
		scoreDom = document.getElementById("scoremessage");
		scoreDom.innerHTML = "Your highest score: "+highestScore;
	}
}


