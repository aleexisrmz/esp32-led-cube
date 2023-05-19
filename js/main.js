var resultado = document.getElementById("resultado");
var servidor = document.getElementById("servidor");

var clientId = 'client_id_' + Math.floor((Math.random() + 1000000) + 1);
client = new Paho.MQTT.Client("broker.emqx.io", 8084, clientId);

client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

var options = {
    useSSL: true,
    userName: "asdasd",
    password: "asdasd",
    onSuccess: onConnect,
    onFailure: doFail
}

client.connect(options);

            function onConnect() {
                servidor.innerHTML = "Conexión exitosa :)";
                client.subscribe("salidaYellow");
            }

            function onMessageArrived(message) {
                resultado.innerHTML = "Un mensaje ha llegado :O  -> " + message.payloadString;
            }

            function doFail(e) {
                resultado.innerHTML = e;
            }

            function onConnectionLost(responseObject) {
                if (responseObject.errorCode !== 0) {
                    resultado.innerHTML = "onConnectionLost: " + responseObject.errorMessage;
                }
            }
            
            function command(value) {
                console.log(value);
                message = new Paho.MQTT.Message(value + "");
                message.destinationName = "entrada";
                client.send(message);
            }