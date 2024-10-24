package com.example.demo.servicies;

import com.example.demo.entities.creditEntity;
import com.example.demo.repositories.creditRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Service
public class creditService {

    @Autowired
    creditRepository CreditRepository;

    public ArrayList<creditEntity> getUserCredits(long userId){
        return CreditRepository.findByCreditUserId(userId);
    }

    public ArrayList<creditEntity> getPhaseCredits(int creditPhase){
        return CreditRepository.findByCreditPhase(creditPhase);
    }

    public creditEntity getCredit(long creditId){
        return CreditRepository.findByCreditId(creditId);
    }

    public creditEntity saveCredit(creditEntity credit){
        return CreditRepository.save(credit);
    }

    public creditEntity updateCredit(creditEntity credit){
        return CreditRepository.save(credit);
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
        double administration = requestedAmount * 0.01;
        double monthlyAmount = creditAmountSimulation(requestedAmount,interest,years);
        return monthlyAmount + administration + desgravamen;
    }

    public double finalCreditAmount(double monthlyAmount,int years){

        int months = years * 12;
        return monthlyAmount*months;
    }
}
