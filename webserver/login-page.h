const char login_page[] PROGMEM = R"=====(
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
			<h1>
				LOGIN
			</h1>
		</div>
		<div>
			<form action="/login" method="POST" class="form">
				<p>This page requires a password to access.</p>
				<input type="text" placeholder="Password" name="password">
				<input type="submit" value="Login">
			</form>
		</div>
  </body>
</html>    
)=====";