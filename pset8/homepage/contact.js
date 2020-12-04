function validation() {
  var name = document.getElementById("name").value;
  var phone = document.getElementById("phone").value;
  var email = document.getElementById("email").value;
  var message = document.getElementById("message").value;
  var error_message = document.getElementById("error_message");
  var text;

  error_message.style.padding = "10px";

  if (name.length < 5) {
    text = "Please Enter valid Name";
    error_message.innerHTML = text;
    return false;
  }

  if (isNaN(phone) || phone.length != 10) {
    text = "Please Enter valid Valid Number";
    error_message.innerHTML = text;
    return false;
  }

  if (email.indexOf("@") == -1 || email.length < 6) {
    text = "Please Enter Valid E-mail";
    error_message.innerHTML = text;
    return false;
  }

  if (message.length <= 10) {
    text = "Please Enter Atleast 10 Charecters";
    error_message.innerHTML = text;
    return false;
  }
  alert("Form submitted Successfully!");
  return true;
}
