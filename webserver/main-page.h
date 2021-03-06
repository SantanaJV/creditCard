const char main_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>ESP8266 WebServer</title>
		<style>
			body {
				background-color: rgb(196, 50, 50);
				font-family: Helvetica, Arial, sans-serif;
				margin: 0;
				padding: 0;
				transition:all 500ms;
			}

			.header h1 {
				color: #EEE;
				margin: 0 0 0 20px;
				align-self: center;
			}

			.header {
				background-color: rgb(163, 18, 18);
				height: 50px;
				display: flex;
			}

			.content {
				margin-left: 20px;
				display: inherit;
			}

			.content-block p {
				color: #eee;
				margin: 0 0 5px 0;
			}

			.content-block {
				margin: 10px 0 10px 0;
			}

			.submit {
				border: 2px solid white;
				font-size: 20px;
				border-radius: 10px;
				color: white;
				background-color: transparent;
				transition:all 250ms;
				outline: none!important;
			}

			.submit:hover {
				color: black;
				background-color: white;
			}

			.text-input {
				border: 1.5px solid #BBB;
				border-radius: 10px;
				width: 350px;
				padding: 5px;
				font-size: 20px;
				outline: none!important;
			}

			.text-input:focus {
				background-color: white;
			}

			#unregisterButton {
				display: none;
			}

		</style>
  </head>
  <body>
		<div class="header">
			<h1 id="title">
				Aguardando cartão...
			</h1>
		</div>
		<div class="content" id="content">
			<div class="content-block">
				<p class="content-block-label">Nome</p>
				<input class="text-input" type="text" id="nome">
			</div>
			<div class="content-block">
				<p class="content-block-label">Série</p>
				<input class="text-input" type="text" id="grade">
			</div>
			<div class="content-block">
				<p class="content-block-label">Saldo</p>
				<input class="text-input" type="number" id="balance">
			</div>
			<input type="button" value="Descadastrar" class="submit" id="unregisterButton" onclick="deleteRfid()" disabled>
			<input type="button" value="Cadastrar" class="submit" id="registerButton" onclick="writeRfid()" disabled>
		</div>
		<script>
            var cardSelected = false;
            var isRegistered = false;
            var rfid = {};

			function writeRfid() {
				
            }
            
            function updateRfid() {

            }

			function deleteRfid() {
				var xhttp = new XMLHttpRequest();
				xhttp.open('DELETE', 'user');
			}

			setInterval(function () {
				getRfidData();
			}, 5000);

			function getRfidData () {
				var xhttp = new XMLHttpRequest();
				xhttp.onreadystatechange = function() {
					if(this.readyState == 4 && this.status == 200) {
						data = JSON.parse(this.response);
						
						if(!data) {
							return;
                        }

                        if(cardSelected)
                            if(rfid.uid == data.rfid.uid) return;
                        
                        rfid = data.rfid;
                        isRegistered = data.registered;
                        
						if(!isRegistered) {
							document.getElementById("unregisterButton").style = "display: none;";
							document.getElementById("registerButton").innerHTML = "Cadastrar";
						} else {
							document.getElementById("unregisterButton").style = "display: inherit;";
							document.getElementById("registerButton").innerHTML = "Salvar Mudanças";

							document.getElementById("content").style = "display: inherit;";
							document.getElementById("title").innerHTML = rfid.uid + " - Aproxime outro cartão para inspecioná-lo";
							document.getElementById("name").innerHTML = rfid.name;
							document.getElementById("grade").innerHTML = rfid.grade;
							document.getElementById("balance").innerHTML = rfid.balance;
							cardSelected = true;
						}
						console.log(response);
						
					}
				};

				xhttp.open("GET", "rfid", true);
				xhttp.send();
			}
		</script>
  </body>
</html>    
)=====";