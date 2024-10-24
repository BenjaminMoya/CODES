import { useState } from "react";
import { useNavigate } from "react-router-dom";
import CalculateIcon from "@mui/icons-material/Calculate";
import Box from "@mui/material/Box";
import PersonAddAltSharpIcon from '@mui/icons-material/PersonAddAltSharp';
import LoginSharpIcon from '@mui/icons-material/LoginSharp';
import TextField from "@mui/material/TextField";
import Button from "@mui/material/Button";
import MenuItem from "@mui/material/MenuItem";
import FormControl from "@mui/material/FormControl";
import userService from "../services/user.service";

const UserLogin = () => {
  const [userName, setUserName] = useState("");
  const [userRut, setUserRut] = useState("");
  const [userEmail, setUserEmail] = useState("");
  const [userPassword, setUserPassword] = useState("");
  const [passwordConfirmation, setPasswordConfirmation] = useState("");
  const [userAge, setUserAge] = useState("");
  const [userAccountSeniority] = useState("0");
  const [userWorkSeniority, setUserWorkSeniority] = useState("");
  const [userSavingCapacity] = useState("-1");
  const [userBalance] = useState("0");
  const [userIndependent, setUserIndependent] = useState("");
  const [executive] = useState("false");
  const [status, setStatus] = useState(false);
  const navigate = useNavigate();
  
  const register = (e) => {
    e.preventDefault();

    const user = { userName, userRut, userEmail, userPassword, userAge, userAccountSeniority, userWorkSeniority, userSavingCapacity, userBalance, userIndependent, executive };
    console.log("Datos del usuario:", user);
    if(userPassword === passwordConfirmation){
        console.log("Solicitar registro de usuario.");
        userService
        .create(user)
        .then((response) => {
        console.log("Usuario registrado: ", response.data);
        if(response.data != null){
            alert("Usuario registrado exitosamente");
        } else {
            alert("Error al registrar usuario");
        }
        })
        .catch((error) => {
            console.log(
                "Ha ocurrido un error al intentar registrar al usuario.",
                error
            );
        });
    } else {
        alert("Las contraseñas no coinciden");
    }
  };

  const login = (e) => {
    e.preventDefault();

    const user = { userEmail, userPassword };
    console.log("Datos del usuario:", user);
    console.log("Solicitar login de usuario.");
    userService
    .login(user)
    .then((response) => {
    console.log("Usuario logeado: ", response.data);
    if(response.data){
        sessionStorage.setItem("userId", JSON.stringify(response.data.userId));
        navigate("/home");
    } else {
        alert("Credenciales invalidas");
    }
    })
    .catch((error) => {
        console.log(
            "Ha ocurrido un error al intentar logearse.",
            error
        );
    });
  };

  const handleEdit = () => {
    setStatus(!status);
  }

  if(status){

    return (
        <Box
          display="flex"
          flexDirection="column"
          alignItems="center"
          justifyContent="center"
          component="form"
        > 
          <div>
            <h3> Login </h3>
          </div>
          <form>
            
            <FormControl fullWidth>
              <TextField
                id="email"
                label="Email"
                value={userEmail}
                variant="standard"
                onChange={(e) => setUserEmail(e.target.value)}
              />
            </FormControl>
    
            <FormControl fullWidth>
              <TextField
                id="password"
                label="Contraseña"
                value={userPassword}
                variant="standard"
                onChange={(e) => setUserPassword(e.target.value)}
              />
            </FormControl>
            
            <FormControl>
              <br />
              <Button
                variant="contained"
                color="info"
                onClick={(e) => login(e)}
                style={{ marginLeft: "0.5rem" }}
                startIcon={<LoginSharpIcon />}
              >
                Login
              </Button>
            </FormControl>

            <FormControl>
              <br />
              <Button
                variant="contained"
                color="info"
                onClick={() => handleEdit()}
                style={{ marginLeft: "0.5rem" }}
                startIcon={<PersonAddAltSharpIcon />}
              >
                Registrarse
              </Button>
            </FormControl>
          </form>
        </Box>
      );
  } else {

    return (
        <Box
          display="flex"
          flexDirection="column"
          alignItems="center"
          justifyContent="center"
          component="form"
        > 
          <div>
            <h3> Registro </h3>
          </div>
          <form>
            
            <FormControl fullWidth>
              <TextField
                id="name"
                label="Nombre"
                value={userName}
                variant="standard"
                onChange={(e) => setUserName(e.target.value)}
              />
            </FormControl>
    
            <FormControl fullWidth>
              <TextField
                id="rut"
                label="Rut"
                value={userRut}
                variant="standard"
                onChange={(e) => setUserRut(e.target.value)}
                helperText="Ej: 12345678-9"
              />
            </FormControl>
    
            <FormControl fullWidth>
              <TextField
                id="email"
                label="Email"
                value={userEmail}
                variant="standard"
                onChange={(e) => setUserEmail(e.target.value)}
              />
            </FormControl>

            <FormControl fullWidth>
              <TextField
                id="password"
                label="Contraseña"
                value={userPassword}
                variant="standard"
                onChange={(e) => setUserPassword(e.target.value)}
              />
            </FormControl>

            <FormControl fullWidth>
              <TextField
                id="password2"
                label="Repetir contraseña"
                value={passwordConfirmation}
                variant="standard"
                onChange={(e) => setPasswordConfirmation(e.target.value)}
              />
            </FormControl>

            <FormControl fullWidth>
              <TextField
                id="age"
                label="Edad"
                value={userAge}
                variant="standard"
                onChange={(e) => setUserAge(e.target.value)}
              />
            </FormControl>

            <FormControl fullWidth>
              <TextField
                id="seniority"
                label="Antiguedad laboral"
                value={userWorkSeniority}
                variant="standard"
                onChange={(e) => setUserWorkSeniority(e.target.value)}
              />
            </FormControl>

            <FormControl fullWidth>
                <TextField
                id="indepedent"
                label="Trabajador independiente"
                value={userIndependent}
                select
                variant="standard"
                defaultValue="1"
                onChange={(e) => setUserIndependent(e.target.value)}
                style={{ width: "25%" }}
                >
            <MenuItem value={"true"}>Si</MenuItem>
            <MenuItem value={"false"}>No</MenuItem>
          </TextField>
        </FormControl>
            
            <FormControl>
              <br />
              <Button
                variant="contained"
                color="info"
                onClick={(e) => register(e)}
                style={{ marginLeft: "0.5rem" }}
                startIcon={<PersonAddAltSharpIcon />}
              >
                Registro
              </Button>
            </FormControl>

            <FormControl>
              <br />
              <Button
                variant="contained"
                color="info"
                onClick={(e) => handleEdit(e)}
                style={{ marginLeft: "0.5rem" }}
                startIcon={<LoginSharpIcon />}
              >
                Logeo
              </Button>
            </FormControl>
          </form>
        </Box>
      );
  }
};

export default UserLogin;