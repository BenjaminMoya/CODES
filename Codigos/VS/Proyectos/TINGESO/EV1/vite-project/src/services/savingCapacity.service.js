import httpCommon from "../http-common";

const min = (id,amount) => {
    return httpCommon.post(`api/saving/min/${id}`,{params:{amount}});
}

const history = (id,balance,max) => {
    return httpCommon.get(`api/saving/history/${id}`,{params:{balance,max}});
}

const periodic = (id,deposit,entry,isPeriodic) => {
    return httpCommon.post(`api/saving/periodic/${id}`,{params:{deposit,entry,isPeriodic}});
}

const relation = (id,amount) => {
    return httpCommon.post(`api/saving/relation/${id}`,{params:{amount}});
}

const out = (id,monthly,balance) => {
    return httpCommon.post(`api/saving/out/${id}`,{params:{monthly,balance}});
}

export default { min, history, periodic, relation, out };