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
    colorPicker.on('color:change', function (color) {
        // log the current color as a HEX string
        console.log(color.rgb);
        httpGet(`/color?r=${color.rgb.r}&g=${color.rgb.g}&b=${color.rgb.b}`);
    });

    function httpGet(theUrl) {
        var xmlHttp = new XMLHttpRequest();
        xmlHttp.open("GET", theUrl, false); // false for synchronous request
        xmlHttp.send(null);
        return xmlHttp.responseText;
    }
</script>

</html>


)=====";