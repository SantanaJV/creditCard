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

			.form {
				margin-left: 20px;
				justify-content: center;
			}

			.form p {
				color: #eee;
			}

		</style>
  </head>
  <body>
		<div class="header">
			<h1 id="title">
				JSON TEST
			</h1>
		</div>
		<script>
			setInterval(function () {
				getData();
			}, 5000);

			function getData () {
				var response;
				var xhttp = new XMLHttpRequest();
				xhttp.onreadystatechange = function() {
					if(this.readyState == 4 && this.status == 200) {
						response = this.response;
						console.log("Got response: ");
						console.log(response);
					}
				};

				xhttp.open("GET", "json", true);
				xhttp.send();
			}
		</script>
  </body>
</html>    
)=====";