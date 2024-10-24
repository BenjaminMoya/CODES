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

export default function Sidemenu({ open, toggleDrawer }) {
  const navigate = useNavigate();

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

        <ListItemButton onClick={() => navigate("/credit/list")}>
          <ListItemIcon>
            <EditNotifications />
          </ListItemIcon>
          <ListItemText primary="Evaluar credito" />
        </ListItemButton>

        <ListItemButton onClick={() => navigate("/user/credits")}>
          <ListItemIcon>
            <ListAlt />
          </ListItemIcon>
          <ListItemText primary="Mis creditos" />
        </ListItemButton>
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
