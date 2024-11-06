package com.Application.CreditAdministration.controllers;

import com.Application.CreditAdministration.entities.UserEntity;
import com.Application.CreditAdministration.servicies.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/user")
@CrossOrigin("*")
public class UserController {

    @Autowired
    UserService userService;

    @GetMapping("/get")
    public ResponseEntity<List<UserEntity>> listUsers(){
        List<UserEntity> users = userService.getUsers();
        return ResponseEntity.ok(users);
    }

    @GetMapping("/getById/{userId}")
    public ResponseEntity<UserEntity> getUserById(@PathVariable Long userId) {
        UserEntity user = userService.getUserById(userId);
        return ResponseEntity.ok(user);
    }

    @GetMapping("/getByRut/{userRut}")
    public ResponseEntity<UserEntity> getUserByRut(@PathVariable String userRut){
        UserEntity user = userService.getUserByRut(userRut);
        return ResponseEntity.ok(user);
    }

    @GetMapping("/getByEmail/{userEmail}")
    public ResponseEntity<UserEntity> getUserByEmail(@PathVariable String userEmail){
        UserEntity user = userService.getUserByEmail(userEmail);
        return ResponseEntity.ok(user);
    }

    @PostMapping("/save")
    public ResponseEntity<UserEntity> saveUser(@RequestBody UserEntity user) {
        UserEntity newUser = userService.saveUser(user);
        return ResponseEntity.ok(newUser);
    }

    @PostMapping("/login")
    public ResponseEntity<UserEntity> login(@RequestBody UserEntity user){
        return ResponseEntity.ok(userService.login(user.getUserEmail(),user.getUserPassword()));
    }

    @PostMapping("/zero/{userId}")
    public int zeroSaving(@PathVariable long userId){
        return userService.zeroSaving(userId);
    }

    @PutMapping("/update")
    public ResponseEntity<UserEntity> updateUser(@RequestBody UserEntity user){
        UserEntity userUpdated = userService.updateUser(user);
        return ResponseEntity.ok(userUpdated);
    }

    @PostMapping("/transfer")
    public double transferAmount(@RequestBody Map<String, Object> body){
        long userId = Long.parseLong(body.get("userId").toString());
        long creditId = Long.parseLong(body.get("creditId").toString());
        return userService.transferAmount(userId,creditId);
    }

    @DeleteMapping("/delete/{userId}")
    public ResponseEntity<Integer> deleteUserById(@PathVariable Long userId) throws Exception {
        var isDeleted = userService.deleteUser(userId);
        return ResponseEntity.ok(isDeleted);
    }
}
