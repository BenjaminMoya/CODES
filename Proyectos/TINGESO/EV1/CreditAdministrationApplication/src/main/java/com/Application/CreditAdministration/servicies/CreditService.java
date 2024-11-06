package com.Application.CreditAdministration.servicies;

import com.Application.CreditAdministration.entities.CreditEntity;
import com.Application.CreditAdministration.repositories.CreditRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.ArrayList;

@Service
public class CreditService {

    @Autowired
    CreditRepository creditRepository;

    public ArrayList<CreditEntity> getUserCredits(long userId){
        return creditRepository.findByCreditUserId(userId);
    }

    public ArrayList<CreditEntity> getPhaseCredits(int creditPhase){
        return creditRepository.findByCreditPhase(creditPhase);
    }

    public CreditEntity getCredit(long creditId){
        return creditRepository.findByCreditId(creditId);
    }

    public CreditEntity saveCredit(CreditEntity credit){
        return creditRepository.save(credit);
    }

    public CreditEntity updateCredit(CreditEntity credit){
        return creditRepository.save(credit);
    }

    public int deleteCredit(long creditId) throws Exception {
        try{
            creditRepository.deleteById(creditId);
            return 1;
        } catch (Exception e) {
            return 0;
        }
    }

    public double creditAmountSimulation(double requestedAmount,double interest,int years){

        double convertedInterest = (interest/12)/100;
        double powerPeriod = Math.pow((1+convertedInterest),years*12);
        return Math.ceil(requestedAmount * ( (convertedInterest*powerPeriod) / (powerPeriod-1) ));
    }

    public int relationCI(double requestedAmount,double interest,int years,double monthlyEntry){
        double percentage = creditAmountSimulation(requestedAmount,interest,years)/monthlyEntry;
        if(percentage > 0.35){
            return 0;
        } else {
            return 1;
        }
    }

    //debtsAmount es aquella que ya tiene integrada la cuota proyectada mensual
    public int relationDI(double monthlyAmount,double debtsMonthlyAmount,double creditMonthlyAmount){
        if((monthlyAmount*0.5) > (debtsMonthlyAmount + creditMonthlyAmount)){
            return 1;
        } else {
            return 0;
        }
    }

    public double finalMonthlyAmount(double requestedAmount,double interest,int years){

        double desgravamen = requestedAmount * 0.0003;
        double monthlyAmount = creditAmountSimulation(requestedAmount,interest,years);
        return monthlyAmount + 20000 + desgravamen;
    }

    public double finalCreditAmount(double monthlyAmount,int years,double requestedAmount){

        int months = years * 12;
        return monthlyAmount*months + requestedAmount*0.01;
    }
}
