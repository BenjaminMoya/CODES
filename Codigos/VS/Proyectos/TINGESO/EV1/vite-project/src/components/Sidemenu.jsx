import * as React from "react";
import Box from "@mui/material/Box";
import Drawer from "@mui/material/Drawer";
import List from "@mui/material/List";
import Divider from "@mui/material/Divider";
import ListItemButton from "@mui/material/ListItemButton";
import ListItemIcon from "@mui/material/ListItemIcon";
import ListItemText from "@mui/material/ListItemText";
import AddCircleOutline from '@mui/icons-material/AddCircleOutline';
import EditNotifications from '@mui/icons-material/EditNotifications';
import ListAlt from '@mui/icons-material/ListAlt';
import Calculate from "@mui/icons-material/Calculate";
import HomeIcon from "@mui/icons-material/Home";
import { useNavigate } from "react-router-dom";
import userService from "../services/user.service";
import { useEffect, useState } from "react";


export default function Sidemenu({ open, toggleDrawer }) {

  const userId = JSON.parse(sessionStorage.getItem("userId"));
  const [executive, setExecutive] = useState(false);
  const [logged, setLogged] = useState(false);
  const navigate = useNavigate();

  const init = () => {
    userService
    .getById(userId)
    .then((response) => {
      setExecutive(response.data.executive);
      if(userId){
        setLogged(true);
      }
    })
    .catch((error) => {
      console.log(
        "Se ha producido un error al intentar mostrar datos del usuario.",
        error
      );
    });
  };

  useEffect(() => {
    init();
  }, []);

  const listOptions = () => (
    <Box
      role="presentation"
      onClick={toggleDrawer(false)}
    >
      <List>
        <ListItemButton onClick={() => navigate("/home")}>
          <ListItemIcon>
            <HomeIcon />
          </ListItemIcon>
          <ListItemText primary="Home" />
        </ListItemButton>

        <Divider />

        <ListItemButton onClick={() => navigate("/credit/simulation")}>
          <ListItemIcon>
            <Calculate />
          </ListItemIcon>
          <ListItemText primary="Simulacion de credito" />
        </ListItemButton>

        <ListItemButton onClick={() => navigate("/credit/application")}>
          <ListItemIcon>
            <AddCircleOutline />
          </ListItemIcon>
          <ListItemText primary="Solicitar credito" />
        </ListItemButton>
      { executive && (
        <ListItemButton onClick={() => navigate("/credit/list")}>
          <ListItemIcon>
            <EditNotifications />
          </ListItemIcon>
          <ListItemText primary="Evaluar credito" />
        </ListItemButton>
      )}
      { !executive && (
        <ListItemButton>
          <ListItemIcon>
            <EditNotifications />
          </ListItemIcon>
          <ListItemText primary="Evaluar credito" />
        </ListItemButton>
      )}
      { logged && (
        <ListItemButton onClick={() => navigate("/user/credits")}>
          <ListItemIcon>
            <ListAlt />
          </ListItemIcon>
         <ListItemText primary="Mis creditos" />
        </ListItemButton>
      )}
      { !logged && (
        <ListItemButton>
          <ListItemIcon>
            <ListAlt />
          </ListItemIcon>
         <ListItemText primary="Mis creditos" />
        </ListItemButton>
      )}
      </List>
    </Box>
  );

  return (
    <div>
      <Drawer anchor={"left"} open={open} onClose={toggleDrawer(false)}>
        {listOptions()}
      </Drawer>
    </div>
  );
}
