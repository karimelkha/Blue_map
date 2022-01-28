function dessin(pos_x, pos_y)
{
    var canvas = document.getElementById('canvas');
    var ctx = canvas.getContext('2d');
    let i;
    for(i = 0; i != pos_x.length-1 || i != pos_y.length-1; i++)
    {
        ctx.beginPath();
        ctx.strokeStyle = 'blue';
        ctx.moveTo(pos_x[i] , pos_y[i]);
        ctx.lineTo(pos_x[i+1],pos_y[i+1]);
        ctx.stroke();
    }
}


var pos_x = [20,100,200,156,98,176,456,210]
var pos_y = [20,100,200,156,98,176,456,210]

dessin(pos_x,pos_y)

function click_function()
{
    var xhttp = new XMLHttpRequest();
    var beacon_id = document.getElementById('beaconList').value;

    xhttp.responseType = 'json';
    console.log("beacon_id: "+beacon_id);
    xhttp.open("GET","usr/"+beacon_id, true);

    xhttp.onreadystatechange = function()
    {
        if(xhttp.readyState == 4 && xhttp.status == 200) {
            // TODO : AJOUTER Dessin  a voir sur map
            dessin([0,xhttp.response["x"]],[0,xhttp.response["y"]]);
        }
    }

    xhttp.send('');

    return xhttp.ResponseText;
}

var button1 = document.getElementById('dessiner');
button1.onclick = click_function;



