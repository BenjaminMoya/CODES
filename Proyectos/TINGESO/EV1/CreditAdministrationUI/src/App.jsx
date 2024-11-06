import './App.css'
import {HashRouter as Router, Route, Routes} from 'react-router-dom'
import Navbar from "./components/Navbar"
import Home from './components/Home';
import UserLogin from './components/UserLogin';
import CreditApplication from './components/CreditApplication';
import CreditSimulation from './components/CreditSimulation';
import CreditsList from './components/CreditsList';
import CreditEvaluation from './components/CreditEvaluation';
import UserCredits from './components/UserCredits';

function App() {
  return (
      <Router>
          <div className="container">
          <Navbar></Navbar>
            <Routes>
              <Route path="/home" element={<Home/>} />
              <Route path="/user/login" element={<UserLogin/>} />
              <Route path="/credit/simulation" element={<CreditSimulation/>} />
              <Route path="/credit/application" element={<CreditApplication/>} />
              <Route path="/credit/list" element={<CreditsList/>} />
              <Route path="/credit/evaluation" element={<CreditEvaluation/>} />
              <Route path="/user/credits" element={<UserCredits/>} />
            </Routes>
          </div>
      </Router>
  );
}

export default App
