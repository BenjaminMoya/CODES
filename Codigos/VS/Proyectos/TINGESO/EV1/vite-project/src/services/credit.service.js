import httpCommon from "../http-common";

const getAll = (id) => {
  return httpCommon.get(`/api/credit/credits/${id}`);
}

const create = (data) => {
  return httpCommon.post('/api/credit/save', data);
}

const expired = (id) => {
    return httpCommon.put(`/api/credit/expired/${id}`);
}

const update = (data) => {
    return httpCommon.put('/api/credit/update', data);
}

const simulation = (amount,interest,years) => {
    return httpCommon.post('/api/credit/simulation',{params:{amount,interest,years}});
}

const relation1 = (amount,entry) => {
    return httpCommon.post('/api/credit/relation1',{params:{amount,entry}});
}

const relation2 = (amount,debts,monthly) => {
    return httpCommon.post('/api/credit/relation2',{params:{amount,debts,monthly}});
}

const max = (type,amount) => {
    return httpCommon.post('/api/credit/max',{params:{type,amount}});
}

const monthly = (amount,interest,years) => {
    return httpCommon.post('/api/credit/monthly',{params:{amount,interest,years}});
}

const final = (amount,years) => {
    return httpCommon.post('/api/credit/final',{params:{amount,years}});
}

export default { getAll, create, expired, update, simulation, relation1, relation2, max, monthly, final };