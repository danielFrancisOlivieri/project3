// variables to show when processes are busy 
				var XMLHttp, busy = false,
				    getProcListBusy = false;
				var previouslySentComments = ["$END"]; // prevents duplication
				// initializes
				function init() {
				        if (navigator.appName == "Microsoft Internet Explorer") {
				            XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
				        } else {
				            XMLHttp = new XMLHttpRequest();
				        }
				    }
				    // gets messages from server
				function getProcList() {
				    if (!getProcListBusy) {
				        getProcListBusy = true;
				        var commentClass = "comment";
				        var outMessage = "***$request$END";
				        if (outMessage.length < 0) return;
				        XMLHttp.open("GET", "/cgi-bin/olivierid_JAD_chatAjax.cgi?" + "outMessage=" + outMessage, true);
				        XMLHttp.onreadystatechange = function() {
				            if (XMLHttp.readyState == 4) {

				                var fromCGI = XMLHttp.responseText;
				                console.log("From CGI: " + fromCGI);
				                var isNew = true;

				                for (i = 0; i < previouslySentComments.length; i++) {

				                    if (previouslySentComments[i].includes(fromCGI)) {

				                        isNew = false;
				                        break;
				                    }
				                }
				                //console.log ("Ready to display:"+fromCGI);
				                if (isNew) {

				                    // changing certain words 
				                    fromCGI = fromCGI.replace("$END", "");
				                    fromCGI = fromCGI.replace("Daniel", "my hero Daniel");
				                    fromCGI = fromCGI.replace("fuck", "f***");
				                    fromCGI = fromCGI.replace("damn", "drat");
				                    fromCGI = fromCGI.replace("hell", "heck");
				                    fromCGI = fromCGI.replace("cuck", "liberal");
				                    fromCGI = fromCGI.replace("Trump", "Drumpf");
				                    fromCGI = fromCGI.replace("Juvi", "the programmer formerly know as Juvi");
				                    fromCGI = fromCGI.replace("Aidan", "Alexander Hamilton");
				                    $('.comment').remove();
				                    $("#chatbox").append(" <div class = " + commentClass + " > <b>" + fromCGI + "</b> </div>");
				                    previouslySentComments.push(fromCGI);
				                }
				                getProcListBusy = false;
				            }
				        }
				        XMLHttp.send(null);

				    } else {
				        console.log("ProcList is busy!");
				    }

				}

				var intVar;

				function AutoRefresh() {

				    intVar = setInterval(function() {
				        getProcList()
				    }, 2000); // calls the function getProclist at regular intervals
				}

				function StopRefresh() {
				    clearInterval(intVar);
				}


				function getUsername() {

				    var name = document.getElementById('userName').value;
				    document.getElementById('user').innerHTML = name;
				    commentObject.username = name;
				    document.getElementById('userName').disabled = true;
				    
				    var div = document.getElementById('chatbox');
				    div.style.visibility= 'visible';
				}
				
		
				function logOut()
				{
				 
				 document.getElementById('userName').disabled = false;
				 
				 alert("Do you want to Log Out? This will delete the chats.");
				 
				 /*if(confirm("Do you want to Log Out? This will delete the chats."))
   				 document.forms[0].submit();
 				 else
 				   return false; */
 				   
				 var div = document.getElementById('chatbox');
				 div.style.visibility= 'hidden';
				 
				}

				// comment object
				var commentObject = {
				    username: "Hamlet",
				    text: "",
				    color: "black",
				    returnOutputString: function() {
				        return "$USERNAME*" + this.username + "Cato$COLOR*" + this.color + "$PICTURE*three$TEXT*" + this.text + "$END";
				    }

				}

				var XMLHttp, avoidReplication = "";
				if (navigator.appName == "Microsoft Internet Explorer") {
				    XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
				} else {
				    XMLHttp = new XMLHttpRequest();
				}

				// precon: there is a comment
				// postcon: sends the text in the input bar
				function sendComment() {

				    if (busy == true) {} else {
				        var message = document.getElementById('usermsg').value;
				        busy = true;

				        if (message.length > 1) {
				            console.log("inMessage is: " + message);
				            // if (name.length < 1) return;

				            commentObject.text = message;
				            message = commentObject.username + ": " + message + "$END";

				            XMLHttp.open("GET", "/cgi-bin/olivierid_JAD_chatAjax.cgi?" + "message=" + message, true);


				            XMLHttp.send(null);
				            busy = false;
				        }



				    }

				}

				$(document).ready(function() {
				    AutoRefresh();
				});
