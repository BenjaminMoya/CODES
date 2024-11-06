import * as React from "react";
import { useNavigate } from "react-router-dom";
import AppBar from "@mui/material/AppBar";
import Box from "@mui/material/Box";
import Toolbar from "@mui/material/Toolbar";
import Typography from "@mui/material/Typography";
import Button from "@mui/material/Button";
import IconButton from "@mui/material/IconButton";
import MenuIcon from "@mui/icons-material/Menu";
import Sidemenu from "./Sidemenu";
import { useState, useEffect } from "react";

export default function Navbar() {
  const [open, setOpen] = useState(false);
  const [logged, setLogged] = useState(false);
  const navigate = useNavigate();

  useEffect(() => {
    init();
  }, []);

  const init = () => {
    if(JSON.parse(sessionStorage.getItem("userId"))){
      setLogged(true);
    }
    navigate("/home");
  }

  const toggleDrawer = (open) => (event) => {
    setOpen(open);
  };

  const login = () => {
    navigate("/user/login");
  };

  const unlog = () => {
    sessionStorage.setItem("userId", JSON.stringify(0));
    setLogged(false);
    navigate("/home");
  }

  return (
    <Box sx={{ flexGrow: 1 }}>
      <AppBar position="static">
        <Toolbar>
          <IconButton
            size="large"
            edge="start"
            color="inherit"
            aria-label="menu"
            sx={{ mr: 2 }}
            onClick={toggleDrawer(true)}
          >
            <MenuIcon />
          </IconButton>

          <Typography variant="h6" component="div" sx={{ flexGrow: 1 }}>
          Banco Usachin
          </Typography>
          {!logged && (
            <Button 
              color="inherit"
              onClick={() => login()}
            >
              Login
            </Button>
          )}
          {logged && (
            <Button 
              color="inherit"
              onClick={() => unlog()}
            >
              Cerrar sesion
            </Button>
          )}    
        </Toolbar>
      </AppBar>

      <Sidemenu open={open} toggleDrawer={toggleDrawer}></Sidemenu>
    </Box>
  );
}
