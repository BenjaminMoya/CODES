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

    @GetMapping("/userCredits/{userId}")
    public ResponseEntity<ArrayList<creditEntity>> getUserCredits(@PathVariable long userId){
        List<creditEntity> credits = CreditService.getUserCredits(userId);
        return ResponseEntity.ok((ArrayList<creditEntity>) credits);
    }

    @GetMapping("/userExpireDebts")
    public ResponseEntity<ArrayList<creditEntity>> getUserExpiredDebts(@RequestBody userEntity user){
        return ResponseEntity.ok((ArrayList<creditEntity>) CreditService.getUserExpiredDebts(user));
    }

    @GetMapping("/creditAmountSimulation")
    public double creditAmountSimulation(@PathVariable double requestedAmount,@PathVariable double interest,@PathVariable int years){
        return CreditService.creditAmountSimulation(requestedAmount,interest,years);
    }

}
