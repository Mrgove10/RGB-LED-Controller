const char HTML_index[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <title>RGB Controller</title>
    <!--CSS-->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/css/bootstrap.min.css" rel="stylesheet"
        integrity="sha384-giJF6kkoqNQ00vy+HMDP7azOuL0xtbfIcaT9wjKHr8RbDVddVHyTfAAsrekwKmP1" crossorigin="anonymous">
    <!--JS-->
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-ygbV9kiqUc6oa4msXn9868pTtWMgiQaeYH7/t7LECLbyPA2x65Kgf80OJFdroafW"
        crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/@jaames/iro@5"></script>
</head>

<body>
    <div class="row">
        <div class="col-md-6">
            <center>
                <b>RGB Controller</b><br>
                <button class="btn btn-success" onclick='httpGet("/power/on")'>on</button>
                <button class="btn btn-danger" onclick='httpGet("/power/off")'>off</button>
            </center>
        </div>
        <div class="col-md-6">
            <center>
                <div id="picker"></div>
            </center>
        </div>
    </div>

</body>

<script>
    var colorPicker = new iro.ColorPicker('#picker');
    httpGetAsync(`/current`, init);

    function init(currentRGBValues) {
        console.log(currentRGBValues);
        currentRGBValues = JSON.parse(currentRGBValues);
        console.log(currentRGBValues);
        let rgbString = `rgb(${currentRGBValues.R},${currentRGBValues.G}, ${currentRGBValues.B})`
        console.log(rgbString);
        colorPicker.setChannel('rgb', 'r', currentRGBValues.R);
        colorPicker.setChannel('rgb', 'g', currentRGBValues.G);
        colorPicker.setChannel('rgb', 'b', currentRGBValues.B);
    }

    colorPicker.on('color:change', function (color) {
        // log the current color as a HEX string
        console.log(color.rgb);
        httpGetAsync(`/color?r=${color.rgb.r}&g=${color.rgb.g}&b=${color.rgb.b}`, null);
    });

    function httpGetAsync(theUrl, callback) {
        var xmlHttp = new XMLHttpRequest();
        xmlHttp.onreadystatechange = function () {
            if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
                callback(xmlHttp.responseText);
        }
        xmlHttp.open("GET", theUrl, true); // true for asynchronous 
        xmlHttp.send(null);
    }
</script>

</html>

)=====";