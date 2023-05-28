String homepageLock = F(R"=====(
<!DOCTYPE html>
<html>
  <head>
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
     body {
      background-color: teal;
      background-size: cover;
      background-position: center;    
    } 
     .flex-row{
       display: flex;
       flex-direction: column;
       align-items: center;
     }
     .flex-keypad{
       display: flex;
       flex-direction: row;
       align-items: center;
       justify-content: center;
     }
     .myButton{
       background-color: LightGrey;
       margin: 10px;
       padding: 10px;
       width: 20%;
       font-size: 30px;
       text-align: center;
     }
     .myButton:hover{
       background-color:green;
     }
     h1{
       font: bold;
       font-size: 50px;
       font-family: Calibri;
       color: Black;
     }
     p{
       font-size: 30px;
       font-family: Calibri;
       color: Black;
     }
    </style>
  </head>
  <body>    
      <div class="flex-row">
        <h1> Smart Safe Access Control </h1>
          <img src = "https://art.pixilart.com/sr25a6f86a07f38.png"
          	width="600"
            height="600"/>        
          <p>Press the Lock button to disable access to the safe, or Unlock to re-enable access</p>          
      </div>
      <div class="flex-keypad">
        <button class="myButton" onclick="fetch('/sentKeyPressToWebServer?button=L'); window.location.reload();"> Lock</button>
        <button class="myButton" onclick="fetch('/sentKeyPressToWebServer?button=U'); window.location.reload();"> Unlock</button>
      </div>   
  </body>
</html>
)=====");

String homepageUnlock = F(R"=====(
<!DOCTYPE html>
<html>
  <head>
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
     body {
      background-color: teal;
      background-size: cover;
      background-position: center;    
    } 
     .flex-row{
       display: flex;
       flex-direction: column;
       align-items: center;
     }
     .flex-keypad{
       display: flex;
       flex-direction: row;
       align-items: center;
       justify-content: center;
     }
     .myButton{
       background-color: LightGrey;
       margin: 10px;
       padding: 10px;
       width: 20%;
       font-size: 30px;
       text-align: center;
     }
     .myButton:hover{
       background-color:green;
     }
     h1{
       font: bold;
       font-size: 50px;
       font-family: Calibri;
       color: Black;
     }
     p{
       font-size: 30px;
       font-family: Calibri;
       color: Black;
     }
    </style>
  </head>
  <body>    
      <div class="flex-row">
        <h1> Smart Safe Access Control </h1>
          <img src = "https://art.pixilart.com/sr2bcc277b0ea0c.png"
          	width="600"
            height="600"/>        
          <p>Press the Lock button to disable access to the safe, or Unlock to re-enable access</p>          
      </div>
      <div class="flex-keypad">
        <button class="myButton" onclick="fetch('/sentKeyPressToWebServer?button=L'); window.location.reload();"> Lock</button>
        <button class="myButton" onclick="fetch('/sentKeyPressToWebServer?button=U'); window.location.reload();"> Unlock</button>
      </div>   
  </body>
</html>
)=====");
//Saved in flash memory as a constant string literal