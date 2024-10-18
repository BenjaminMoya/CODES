import './App.css'
import {BrowserRouter as Router, Route, Routes} from 'react-router-dom'
import Navbar from "./components/Navbar"
import Home from './components/Home';
import CreditApplication from './components/CreditApplication';
import CreditSimulation from './components/CreditSimulation';

function App() {
  return (
      <Router>
          <div className="container">
          <Navbar></Navbar>
            <Routes>
              <Route path="/home" element={<Home/>} />
              <Route path="/credit/simulation" element={<CreditSimulation/>} />
              <Route path="/credit/application" element={<CreditApplication/>} />
            </Routes>
          </div>
      </Router>
  );
}

export default App
