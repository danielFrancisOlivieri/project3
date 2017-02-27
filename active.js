
var XMLHttp;

function init() {
    if(navigator.appName == "Microsoft Internet Explorer") {
	XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
    } else {
	XMLHttp = new XMLHttpRequest();
    }
}

function getProcList () {

    var uname = document.getElementById('uname').value;

    if (uname.length < 1) return;

    XMLHttp.open("GET", "/usr/lib/cgi-bin/$(USER)_JAD_chatAjax.cgi?"
		 + "uname=" + uname
		 ,true);
    XMLHttp.onreadystatechange=function() {

	document.getElementById('response_area').innerHTML = XMLHttp.responseText;;

    }
    XMLHttp.send(null);
}

var intVar;
function AutoRefresh() {

    intVar = setInterval(function(){ getProcList()}, 1000);
}

function StopRefresh() {
    clearInterval(intVar);
}
