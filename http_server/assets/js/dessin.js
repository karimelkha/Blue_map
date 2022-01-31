function dessin(pos_x, pos_y)
{
    var canvas = document.getElementById('canvas');
    var ctx = canvas.getContext('2d');
    let i;
    ctx.clearRect(0,0,ctx.width,ctx.height);
    for(i = 0; i != pos_x.length-1 || i != pos_y.length-1; i++)
    {
        ctx.beginPath();
        ctx.strokeStyle = 'blue';
        ctx.moveTo(pos_x[i] , pos_y[i]);
        ctx.lineTo(pos_x[i+1],pos_y[i+1]);
        ctx.stroke();
    }
}
function cercle(pos_x,pos_y){
    var canvas = document.getElementById('canvas');
    var ctx = canvas.getContext('2d');

    ctx.clearRect(0,0,canvas.width,canvas.height);
   
    ctx.beginPath();
    ctx.strokeStyle = 'red';
    ctx.arc(pos_x,pos_y, 20, 0, 2 * Math.PI);
    ctx.fillStyle = 'red';
    ctx.fill();
    ctx.stroke();
}


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
            cercle(xhttp.response["x"]*(1000/6,5),xhttp.response["y"]*(500/1,7));
        }
    }
    xhttp.send('');
    return xhttp.ResponseText;
}


var button1 = document.getElementById('dessiner');

button1.onclick = click_function;
window.setInterval(click_function, 2000);



