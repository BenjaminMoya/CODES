package com.example.demo.servicies;

import com.example.demo.entities.creditEntity;
import com.example.demo.repositories.creditRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Date;
import java.util.List;

@Service
public class creditService {

    @Autowired
    creditRepository CreditRepository;

    public List<creditEntity> getUserCredits(long userId){

        return CreditRepository.findByCreditUserId(userId);
    }

    public int saveCredit(creditEntity credit){
        try{
            CreditRepository.save(credit);
            return 1;
        } catch (Exception e) {
            return 0;
        }
    }

    public List<creditEntity> getUserExpiredDebts(long userId){

        Date current = new Date();
        List<creditEntity> userDebt = CreditRepository.findByCreditUserId(userId);
        userDebt.removeIf(credit -> credit.getCreditFinishDate().before(current));
        return userDebt;

    }

    public void updateCredit(creditEntity credit){
        CreditRepository.save(credit);
    }

    public int nextPhase(creditEntity credit){
        int phase = credit.getCreditPhase() + 1;
        credit.setCreditPhase(phase);
        updateCredit(credit);
        return 1;
    }

    public double creditAmountSimulation(double requestedAmount,double interest,int years){

        double convertedInterest = (interest/12)/100;
        double powerPeriod = Math.pow((1+convertedInterest),years*12);
        return requestedAmount * ( (convertedInterest*powerPeriod) / (powerPeriod-1) );
    }

    public int relationCI(double monthlyAmount,double monthlyEntry){
        double percentage = monthlyAmount/monthlyEntry;
        if(percentage > 0.35){
            return 0;
        } else {
            return 1;
        }
    }

    //debtsAmount es aquella que ya tiene integrada la cuota proyectada mensual
    public int relationDI(double monthlyAmount,double debtsMonthlyAmount,double creditMonthlyAmount){
        if((monthlyAmount*0.5) > (debtsMonthlyAmount + creditMonthlyAmount)){
            return 0;
        } else {
            return 1;
        }
    }

    public double maxFinancing(int creditType,double propertyAmount){
        if(creditType == 1){
            return propertyAmount*0.8;
        } else if (creditType == 2) {
            return propertyAmount*0.7;
        } else if (creditType == 3) {
            return propertyAmount*0.6;
        } else {
            return propertyAmount*0.5;
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
