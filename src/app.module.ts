import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';

import { TypeOrmModule, TypeOrmModuleOptions } from '@nestjs/typeorm'
import { UserModule } from './modules/user/user.module';
import databaseConfiguration from './configs/database.config'
import {User} from './modules/user/entities/user.entity'

@Module({
  imports: [
    TypeOrmModule.forRoot({
      type: 'mysql',
      host: 'localhost',
      port: 8889, // Remplacer par votre port si différent
      username: 'root',
      password: 'root', // Remplacer par votre mot de passe si différent
      database: 'test',
      entities:[User],
      synchronize: true, // À utiliser uniquement en développement
    }),
    UserModule
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
