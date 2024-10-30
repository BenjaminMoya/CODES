import httpCommon from "../http-common";

const getAll = (id) => {
  return httpCommon.get(`/api/credit/credits/${id}`);
}

const getPhase = (phase) => {
    return httpCommon.get(`/api/credit/phase/${phase}`);
}

const create = (data) => {
  return httpCommon.post('/api/credit/save', data);
}

const update = (data) => {
    return httpCommon.put('/api/credit/update', data);
}

const simulation = (amount,interest,years) => {
    return httpCommon.get('/api/credit/simulation',{params:{amount,interest,years}});
}

const relation1 = (amount,interest,years,entry) => {
    return httpCommon.get('/api/credit/relation1',{params:{amount,interest,years,entry}});
}

const relation2 = (amount,debts,monthly) => {
    return httpCommon.get('/api/credit/relation2',{params:{amount,debts,monthly}});
}

const monthly = (amount,interest,years) => {
    return httpCommon.get('/api/credit/monthly',{params:{amount,interest,years}});
}

const final = (amount,years,requested) => {
    return httpCommon.get('/api/credit/final',{params:{amount,years,requested}});
}

const deleteCredit = (id) => {
    return httpCommon.delete(`/api/credit/delete/${id}`);
}

export default { getAll, getPhase , create, update, simulation, relation1, relation2, monthly, final, deleteCredit };