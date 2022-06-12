## System Architecture

```plantuml

left to right direction




component "Simulink-Basyx Interface" as ml {

	portin p1
	portin p2
	
	component "urlhandler" <<lib>> as url
	component "BasyxConnector" <<lib>> as bc
	component "httpclient" <<lib>> as http
	component "SimulinkBlocks" <<lib>> as simu
	
}
component "jsoncpp" <<lib>> as jsoncpp
component "cURL" <<lib>> as curl

p1 -(0-- curl
p2 -(0-- jsoncpp

http -(0- p1 : HTTP requests
bc -(0- p2 : JSON handler

url-0)-bc 
url-0)-http

http-0)-bc

bc -0)-simu

```