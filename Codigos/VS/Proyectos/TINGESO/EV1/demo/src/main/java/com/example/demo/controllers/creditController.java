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
        return ResponseEntity.ok(CreditService.getUserCredits(userId));
    }

    @GetMapping("/phase/{creditPhase}")
    public ResponseEntity<ArrayList<creditEntity>> getPhaseCredits(@PathVariable int creditPhase){
        return ResponseEntity.ok(CreditService.getPhaseCredits(creditPhase));
    }

    @GetMapping("/getCredit/{creditId}")
    public ResponseEntity<creditEntity> getCredit(@PathVariable long creditId){
        return ResponseEntity.ok(CreditService.getCredit(creditId));
    }

    @PostMapping("/save")
    public ResponseEntity<creditEntity> saveCredit(@RequestBody creditEntity credit){
        try{
            return ResponseEntity.ok(CreditService.saveCredit(credit));
        } catch (Exception e) {
            return null;
        }
    }

    @PostMapping("/update")
    public ResponseEntity<creditEntity> updateCredit(@RequestBody creditEntity credit){
        try{
            return ResponseEntity.ok(CreditService.updateCredit(credit));
        } catch (Exception e) {
            return null;
        }
    }

    @GetMapping("/simulation")
    public double creditAmountSimulation(@RequestParam("amount") double requestedAmount,
                                         @RequestParam("interest") double interest,
                                         @RequestParam("years") int years){
        return CreditService.creditAmountSimulation(requestedAmount,interest,years);
    }

    @GetMapping("/relation1")
    public int relationCI(@RequestParam("amount") double requestedAmount,
                          @RequestParam("interest") double interest,
                          @RequestParam("years") int years,
                          @RequestParam("entry") double monthlyEntry){
        return CreditService.relationCI(requestedAmount,interest,years,monthlyEntry);
    }

    @GetMapping("/relation2")
    public int relationDI(@RequestParam("amount") double monthlyAmount,
                          @RequestParam("debts") double debtsMonthlyAmount,
                          @RequestParam("monthly") double creditMonthlyAmount){
        return CreditService.relationDI(monthlyAmount,debtsMonthlyAmount,creditMonthlyAmount);
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
