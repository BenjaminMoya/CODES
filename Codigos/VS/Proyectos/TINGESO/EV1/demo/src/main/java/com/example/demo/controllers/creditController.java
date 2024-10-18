package com.example.demo.controllers;

import com.example.demo.entities.creditEntity;
import com.example.demo.entities.userEntity;
import com.example.demo.servicies.creditService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RestController
@RequestMapping("/api/credit")
@CrossOrigin("*")
public class creditController {

    @Autowired
    creditService CreditService;

    @GetMapping("/credits/{userId}")
    public ResponseEntity<ArrayList<creditEntity>> getUserCredits(@PathVariable long userId){
        List<creditEntity> credits = CreditService.getUserCredits(userId);
        return ResponseEntity.ok((ArrayList<creditEntity>) credits);
    }

    @PostMapping("/save")
    public int saveCredit(@RequestBody creditEntity credit){
        try{
            CreditService.saveCredit(credit);
            return 1;
        } catch (Exception e) {
            return 0;
        }
    }

    @GetMapping("/expired/{userId}")
    public ResponseEntity<ArrayList<creditEntity>> getUserExpiredDebts(@PathVariable long userId){
        return ResponseEntity.ok((ArrayList<creditEntity>) CreditService.getUserExpiredDebts(userId));
    }

    @PostMapping("/update")
    public int updateCredit(@RequestBody creditEntity credit){
        try{
            CreditService.updateCredit(credit);
            return 1;
        } catch (Exception e) {
            return 0;
        }
    }

    @GetMapping("/simulation")
    public double creditAmountSimulation(@RequestParam("amount") double requestedAmount,
                                         @RequestParam("interest") double interest,
                                         @RequestParam("years") int years){
        return CreditService.creditAmountSimulation(requestedAmount,interest,years);
    }

    @GetMapping("/relation1")
    public int relationCI(@RequestParam("amount") double monthlyAmount,
                          @RequestParam("entry") double monthlyEntry){
        return CreditService.relationCI(monthlyAmount,monthlyEntry);
    }

    @GetMapping("/relation2")
    public int relationDI(@RequestParam("amount") double monthlyAmount,
                          @RequestParam("debts") double debtsMonthlyAmount,
                          @RequestParam("monthly") double creditMonthlyAmount){
        return CreditService.relationDI(monthlyAmount,debtsMonthlyAmount,creditMonthlyAmount);
    }

    @GetMapping("/max")
    public double maxFinancing(@RequestParam("type") int creditType,
                               @RequestParam("amount") double propertyAmount){
        return CreditService.maxFinancing(creditType,propertyAmount);
    }

    @GetMapping("/monthly")
    public double finalMonthlyAmount(@RequestParam("amount") double requestedAmount,
                                     @RequestParam("interest") double interest,
                                     @RequestParam("years") int years){
        return CreditService.finalMonthlyAmount(requestedAmount,interest,years);
    }

    @GetMapping("/final")
    public double finalCreditAmount(@RequestParam("amount") double monthlyAmount,
                                    @RequestParam("years") int years){
        return CreditService.finalCreditAmount(monthlyAmount,years);
    }

}
