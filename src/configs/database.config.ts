import * as dotenv from 'dotenv'
dotenv.config()

const databaseConfiguration = {
  autoLoadEntities: true,
  database: process.env.DATABASE_NAME,
  host: process.env.DATABASE_HOST,
  password: `${process.env.DATABASE_PASSWORD as string}`,
  port: parseInt(process.env.DATABASE_PORT as string) ?? 3306,
  synchronize: true,
  type: process.env.DATABASE_PROVIDER,
  username: process.env.DATABASE_USER
}
export default databaseConfiguration